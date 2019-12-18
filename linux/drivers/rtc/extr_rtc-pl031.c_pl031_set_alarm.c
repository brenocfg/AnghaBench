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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct pl031_local {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_MR ; 
 struct pl031_local* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pl031_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 int rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int pl031_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct pl031_local *ldata = dev_get_drvdata(dev);
	unsigned long time;
	int ret;

	/* At the moment, we can only deal with non-wildcarded alarm times. */
	ret = rtc_valid_tm(&alarm->time);
	if (ret == 0) {
		ret = rtc_tm_to_time(&alarm->time, &time);
		if (ret == 0) {
			writel(time, ldata->base + RTC_MR);
			pl031_alarm_irq_enable(dev, alarm->enabled);
		}
	}

	return ret;
}