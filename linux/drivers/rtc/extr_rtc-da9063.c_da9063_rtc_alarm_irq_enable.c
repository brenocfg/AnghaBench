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

/* Variables and functions */
 int da9063_rtc_start_alarm (struct device*) ; 
 int da9063_rtc_stop_alarm (struct device*) ; 

__attribute__((used)) static int da9063_rtc_alarm_irq_enable(struct device *dev,
				       unsigned int enabled)
{
	if (enabled)
		return da9063_rtc_start_alarm(dev);
	else
		return da9063_rtc_stop_alarm(dev);
}