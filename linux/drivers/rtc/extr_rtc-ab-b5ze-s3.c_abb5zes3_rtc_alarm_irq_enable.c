#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct abb5zes3_rtc_data {scalar_t__ timer_alarm; scalar_t__ irq; } ;

/* Variables and functions */
 int _abb5zes3_rtc_update_alarm (struct device*,unsigned int) ; 
 int _abb5zes3_rtc_update_timer (struct device*,unsigned int) ; 
 struct abb5zes3_rtc_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int abb5zes3_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enable)
{
	struct abb5zes3_rtc_data *rtc_data = dev_get_drvdata(dev);
	int ret = 0;

	if (rtc_data->irq) {
		if (rtc_data->timer_alarm)
			ret = _abb5zes3_rtc_update_timer(dev, enable);
		else
			ret = _abb5zes3_rtc_update_alarm(dev, enable);
	}

	return ret;
}