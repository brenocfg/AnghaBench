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
struct rtc_time {int dummy; } ;
struct pl031_local {scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_LR ; 
 struct pl031_local* dev_get_drvdata (struct device*) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int pl031_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long time;
	struct pl031_local *ldata = dev_get_drvdata(dev);
	int ret;

	ret = rtc_tm_to_time(tm, &time);

	if (ret == 0)
		writel(time, ldata->base + RTC_LR);

	return ret;
}