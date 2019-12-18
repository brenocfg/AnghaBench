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
typedef  int uint8_t ;
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; } ;
struct device {int dummy; } ;
struct da9052_rtc {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_COUNT_S_REG ; 
 int EINVAL ; 
 int da9052_group_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct da9052_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_err (struct da9052_rtc*,char*,int) ; 

__attribute__((used)) static int da9052_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct da9052_rtc *rtc;
	uint8_t v[6];
	int ret;

	/* DA9052 only has 6 bits for year - to represent 2000-2063 */
	if ((tm->tm_year < 100) || (tm->tm_year > 163))
		return -EINVAL;

	rtc = dev_get_drvdata(dev);

	v[0] = tm->tm_sec;
	v[1] = tm->tm_min;
	v[2] = tm->tm_hour;
	v[3] = tm->tm_mday;
	v[4] = tm->tm_mon + 1;
	v[5] = tm->tm_year - 100;

	ret = da9052_group_write(rtc->da9052, DA9052_COUNT_S_REG, 6, v);
	if (ret < 0)
		rtc_err(rtc, "failed to set RTC time: %d\n", ret);
	return ret;
}