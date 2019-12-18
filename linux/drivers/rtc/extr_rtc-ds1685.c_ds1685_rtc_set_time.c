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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;scalar_t__ bcd_mode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EDOM ; 
 int /*<<< orphan*/  RTC_CENTURY ; 
 int /*<<< orphan*/  RTC_CENTURY_MASK ; 
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_DM ; 
 int /*<<< orphan*/  RTC_HRS ; 
 int /*<<< orphan*/  RTC_HRS_24_BCD_MASK ; 
 int /*<<< orphan*/  RTC_HRS_24_BIN_MASK ; 
 int /*<<< orphan*/  RTC_MDAY ; 
 int /*<<< orphan*/  RTC_MDAY_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MDAY_BIN_MASK ; 
 int /*<<< orphan*/  RTC_MINS ; 
 int /*<<< orphan*/  RTC_MINS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MINS_BIN_MASK ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_MONTH_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MONTH_BIN_MASK ; 
 int /*<<< orphan*/  RTC_SECS ; 
 int /*<<< orphan*/  RTC_SECS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_SECS_BIN_MASK ; 
 int /*<<< orphan*/  RTC_WDAY ; 
 int /*<<< orphan*/  RTC_WDAY_MASK ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 int /*<<< orphan*/  RTC_YEAR_BCD_MASK ; 
 int /*<<< orphan*/  RTC_YEAR_BIN_MASK ; 
 struct ds1685_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ds1685_rtc_begin_data_access (struct ds1685_priv*) ; 
 int ds1685_rtc_bin2bcd (struct ds1685_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1685_rtc_end_data_access (struct ds1685_priv*) ; 
 scalar_t__ rtc_month_days (int,int) ; 
 int stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ds1685_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 ctrlb, seconds, minutes, hours, wday, mday, month, years, century;

	/* Fetch the time info from rtc_time. */
	seconds = ds1685_rtc_bin2bcd(rtc, tm->tm_sec, RTC_SECS_BIN_MASK,
				     RTC_SECS_BCD_MASK);
	minutes = ds1685_rtc_bin2bcd(rtc, tm->tm_min, RTC_MINS_BIN_MASK,
				     RTC_MINS_BCD_MASK);
	hours   = ds1685_rtc_bin2bcd(rtc, tm->tm_hour, RTC_HRS_24_BIN_MASK,
				     RTC_HRS_24_BCD_MASK);
	wday    = ds1685_rtc_bin2bcd(rtc, (tm->tm_wday + 1), RTC_WDAY_MASK,
				     RTC_WDAY_MASK);
	mday    = ds1685_rtc_bin2bcd(rtc, tm->tm_mday, RTC_MDAY_BIN_MASK,
				     RTC_MDAY_BCD_MASK);
	month   = ds1685_rtc_bin2bcd(rtc, (tm->tm_mon + 1), RTC_MONTH_BIN_MASK,
				     RTC_MONTH_BCD_MASK);
	years   = ds1685_rtc_bin2bcd(rtc, (tm->tm_year % 100),
				     RTC_YEAR_BIN_MASK, RTC_YEAR_BCD_MASK);
	century = ds1685_rtc_bin2bcd(rtc, ((tm->tm_year + 1900) / 100),
				     RTC_CENTURY_MASK, RTC_CENTURY_MASK);

	/*
	 * Perform Sanity Checks:
	 *   - Months: !> 12, Month Day != 0.
	 *   - Month Day !> Max days in current month.
	 *   - Hours !>= 24, Mins !>= 60, Secs !>= 60, & Weekday !> 7.
	 */
	if ((tm->tm_mon > 11) || (mday == 0))
		return -EDOM;

	if (tm->tm_mday > rtc_month_days(tm->tm_mon, tm->tm_year))
		return -EDOM;

	if ((tm->tm_hour >= 24) || (tm->tm_min >= 60) ||
	    (tm->tm_sec >= 60)  || (wday > 7))
		return -EDOM;

	/*
	 * Set the data mode to use and store the time values in the
	 * RTC registers.
	 */
	ds1685_rtc_begin_data_access(rtc);
	ctrlb = rtc->read(rtc, RTC_CTRL_B);
	if (rtc->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	else
		ctrlb |= RTC_CTRL_B_DM;
	rtc->write(rtc, RTC_CTRL_B, ctrlb);
	rtc->write(rtc, RTC_SECS, seconds);
	rtc->write(rtc, RTC_MINS, minutes);
	rtc->write(rtc, RTC_HRS, hours);
	rtc->write(rtc, RTC_WDAY, wday);
	rtc->write(rtc, RTC_MDAY, mday);
	rtc->write(rtc, RTC_MONTH, month);
	rtc->write(rtc, RTC_YEAR, years);
	rtc->write(rtc, RTC_CENTURY, century);
	ds1685_rtc_end_data_access(rtc);

	return 0;
}