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
struct pcf85363 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int _pcf85363_rtc_alarm_irq_enable (struct pcf85363*,unsigned int) ; 
 struct pcf85363* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int pcf85363_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enabled)
{
	struct pcf85363 *pcf85363 = dev_get_drvdata(dev);

	return _pcf85363_rtc_alarm_irq_enable(pcf85363, enabled);
}