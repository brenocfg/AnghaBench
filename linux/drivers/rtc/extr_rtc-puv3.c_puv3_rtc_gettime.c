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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_RCNR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int puv3_rtc_gettime(struct device *dev, struct rtc_time *rtc_tm)
{
	rtc_time_to_tm(readl(RTC_RCNR), rtc_tm);

	dev_dbg(dev, "read time %ptRr\n", rtc_tm);

	return 0;
}