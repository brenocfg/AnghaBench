#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sunxi_rtc_dev {scalar_t__ base; TYPE_1__* data_year; } ;
struct rtc_time {int tm_year; int tm_mon; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_mday; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int min; unsigned int max; int /*<<< orphan*/  leap_shift; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int SUNXI_DATE_SET_DAY_VALUE (int /*<<< orphan*/ ) ; 
 int SUNXI_DATE_SET_MON_VALUE (int) ; 
 int SUNXI_DATE_SET_YEAR_VALUE (int,int /*<<< orphan*/ ) ; 
 int SUNXI_LEAP_SET_VALUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUNXI_LOSC_CTRL ; 
 int /*<<< orphan*/  SUNXI_LOSC_CTRL_RTC_HMS_ACC ; 
 int /*<<< orphan*/  SUNXI_LOSC_CTRL_RTC_YMD_ACC ; 
 scalar_t__ SUNXI_RTC_HMS ; 
 scalar_t__ SUNXI_RTC_YMD ; 
 int SUNXI_TIME_SET_HOUR_VALUE (int /*<<< orphan*/ ) ; 
 int SUNXI_TIME_SET_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int SUNXI_TIME_SET_SEC_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ SUNXI_YEAR_OFF (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sunxi_rtc_dev* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_leap_year (unsigned int) ; 
 scalar_t__ sunxi_rtc_wait (struct sunxi_rtc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_rtc_settime(struct device *dev, struct rtc_time *rtc_tm)
{
	struct sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date = 0;
	u32 time = 0;
	unsigned int year;

	/*
	 * the input rtc_tm->tm_year is the offset relative to 1900. We use
	 * the SUNXI_YEAR_OFF macro to rebase it with respect to the min year
	 * allowed by the hardware
	 */

	year = rtc_tm->tm_year + 1900;
	if (year < chip->data_year->min || year > chip->data_year->max) {
		dev_err(dev, "rtc only supports year in range %u - %u\n",
			chip->data_year->min, chip->data_year->max);
		return -EINVAL;
	}

	rtc_tm->tm_year -= SUNXI_YEAR_OFF(chip->data_year);
	rtc_tm->tm_mon += 1;

	date = SUNXI_DATE_SET_DAY_VALUE(rtc_tm->tm_mday) |
		SUNXI_DATE_SET_MON_VALUE(rtc_tm->tm_mon)  |
		SUNXI_DATE_SET_YEAR_VALUE(rtc_tm->tm_year,
				chip->data_year->mask);

	if (is_leap_year(year))
		date |= SUNXI_LEAP_SET_VALUE(1, chip->data_year->leap_shift);

	time = SUNXI_TIME_SET_SEC_VALUE(rtc_tm->tm_sec)  |
		SUNXI_TIME_SET_MIN_VALUE(rtc_tm->tm_min)  |
		SUNXI_TIME_SET_HOUR_VALUE(rtc_tm->tm_hour);

	writel(0, chip->base + SUNXI_RTC_HMS);
	writel(0, chip->base + SUNXI_RTC_YMD);

	writel(time, chip->base + SUNXI_RTC_HMS);

	/*
	 * After writing the RTC HH-MM-SS register, the
	 * SUNXI_LOSC_CTRL_RTC_HMS_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	if (sunxi_rtc_wait(chip, SUNXI_LOSC_CTRL,
				SUNXI_LOSC_CTRL_RTC_HMS_ACC, 50)) {
		dev_err(dev, "Failed to set rtc time.\n");
		return -1;
	}

	writel(date, chip->base + SUNXI_RTC_YMD);

	/*
	 * After writing the RTC YY-MM-DD register, the
	 * SUNXI_LOSC_CTRL_RTC_YMD_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	if (sunxi_rtc_wait(chip, SUNXI_LOSC_CTRL,
				SUNXI_LOSC_CTRL_RTC_YMD_ACC, 50)) {
		dev_err(dev, "Failed to set rtc time.\n");
		return -1;
	}

	return 0;
}