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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;
struct meson_rtc {int /*<<< orphan*/  serial; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_COUNTER ; 
 struct meson_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int meson_rtc_gettime(struct device *dev, struct rtc_time *tm)
{
	struct meson_rtc *rtc = dev_get_drvdata(dev);
	u32 time;
	int ret;

	ret = regmap_read(rtc->serial, RTC_COUNTER, &time);
	if (!ret)
		rtc_time64_to_tm(time, tm);

	return ret;
}