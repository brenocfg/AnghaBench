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
struct ftm_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ftm_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ftm_irq_disable (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_irq_enable (struct ftm_rtc*) ; 

__attribute__((used)) static int ftm_rtc_alarm_irq_enable(struct device *dev,
		unsigned int enabled)
{
	struct ftm_rtc *rtc = dev_get_drvdata(dev);

	if (enabled)
		ftm_irq_enable(rtc);
	else
		ftm_irq_disable(rtc);

	return 0;
}