/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_posix.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>

/* defined the LED0 pin: PB5 */
#define LED0_PIN    GET_PIN(F, 6)
/* defined the LED0 pin: PE5 */
#define LED1_PIN    GET_PIN(F, 9)

int main(void)
{
	if(dfs_mount("W25Q128B","/","elm",0,0)==0)
		rt_kprintf("W25Q128B mount to / successed!\n");
	else
		rt_kprintf("W25Q128B mount to / failed!\n");
	
		rt_device_t lcd;
		
		/* find lcd device */
    lcd = rt_device_find("lcd");
		/* set lcd device as rtgui graphic driver */
    rtgui_graphic_set_device(lcd);
		//rtgui_system_server_init();
	#if 0
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
	#endif 
		
    return RT_EOK;
}



#define ADC_DEV_NAME        "adc1"      /* ADC ???? */
#define ADC_DEV_CHANNEL     14           /* ADC ?? */
#define REFER_VOLTAGE       330         /* ???? 3.3V,??????100??2???*/
#define CONVERT_BITS        (1 << 12)   /* ?????12? */

static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    /* ???? */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    /* ???? */
    ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);

    /* ????? */
    value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
    rt_kprintf("the value is :%d \n", value);

    /* ???????? */
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

    /* ???? */
    ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);

    return ret;
}
/* ??? msh ????? */
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);

