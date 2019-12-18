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
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct device {int dummy; } ;
struct da9052_rtc {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_COUNT_S_REG ; 
 int DA9052_GET_TIME_RETRIES ; 
 int DA9052_RTC_DAY ; 
 int DA9052_RTC_HOUR ; 
 int DA9052_RTC_MIN ; 
 int DA9052_RTC_MONTH ; 
 int DA9052_RTC_SEC ; 
 int DA9052_RTC_YEAR ; 
 int EIO ; 
 int da9052_group_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct da9052_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtc_err (struct da9052_rtc*,char*,...) ; 

__attribute__((used)) static int da9052_rtc_read_time(struct device *dev, struct rtc_time *rtc_tm)
{
	struct da9052_rtc *rtc = dev_get_drvdata(dev);
	int ret;
	uint8_t v[2][6];
	int idx = 1;
	int timeout = DA9052_GET_TIME_RETRIES;

	ret = da9052_group_read(rtc->da9052, DA9052_COUNT_S_REG, 6, &v[0][0]);
	if (ret) {
		rtc_err(rtc, "Failed to read RTC time : %d\n", ret);
		return ret;
	}

	do {
		ret = da9052_group_read(rtc->da9052,
					DA9052_COUNT_S_REG, 6, &v[idx][0]);
		if (ret) {
			rtc_err(rtc, "Failed to read RTC time : %d\n", ret);
			return ret;
		}

		if (memcmp(&v[0][0], &v[1][0], 6) == 0) {
			rtc_tm->tm_year = (v[0][5] & DA9052_RTC_YEAR) + 100;
			rtc_tm->tm_mon  = (v[0][4] & DA9052_RTC_MONTH) - 1;
			rtc_tm->tm_mday = v[0][3] & DA9052_RTC_DAY;
			rtc_tm->tm_hour = v[0][2] & DA9052_RTC_HOUR;
			rtc_tm->tm_min  = v[0][1] & DA9052_RTC_MIN;
			rtc_tm->tm_sec  = v[0][0] & DA9052_RTC_SEC;

			return 0;
		}

		idx = (1-idx);
		msleep(20);

	} while (timeout--);

	rtc_err(rtc, "Timed out reading time\n");

	return -EIO;
}