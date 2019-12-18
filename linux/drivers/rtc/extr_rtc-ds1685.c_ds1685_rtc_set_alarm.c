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
typedef  int u8 ;
struct TYPE_2__ {int tm_mon; int tm_year; int tm_wday; int tm_yday; int tm_isdst; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;scalar_t__ bcd_mode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_AIE ; 
 int RTC_CTRL_B_DM ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 int /*<<< orphan*/  RTC_HRS_24_BCD_MASK ; 
 int /*<<< orphan*/  RTC_HRS_24_BIN_MASK ; 
 int /*<<< orphan*/  RTC_HRS_ALARM ; 
 int /*<<< orphan*/  RTC_MDAY_ALARM ; 
 int /*<<< orphan*/  RTC_MDAY_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MDAY_BIN_MASK ; 
 int /*<<< orphan*/  RTC_MINS_ALARM ; 
 int /*<<< orphan*/  RTC_MINS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MINS_BIN_MASK ; 
 int /*<<< orphan*/  RTC_SECS_ALARM ; 
 int /*<<< orphan*/  RTC_SECS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_SECS_BIN_MASK ; 
 struct ds1685_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ds1685_rtc_begin_data_access (struct ds1685_priv*) ; 
 int ds1685_rtc_bin2bcd (struct ds1685_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ds1685_rtc_check_mday (struct ds1685_priv*,int) ; 
 int /*<<< orphan*/  ds1685_rtc_end_data_access (struct ds1685_priv*) ; 
 int stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub10 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub4 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ds1685_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 ctrlb, seconds, minutes, hours, mday;
	int ret;

	/* Fetch the alarm info and convert to BCD. */
	seconds	= ds1685_rtc_bin2bcd(rtc, alrm->time.tm_sec,
				     RTC_SECS_BIN_MASK,
				     RTC_SECS_BCD_MASK);
	minutes	= ds1685_rtc_bin2bcd(rtc, alrm->time.tm_min,
				     RTC_MINS_BIN_MASK,
				     RTC_MINS_BCD_MASK);
	hours	= ds1685_rtc_bin2bcd(rtc, alrm->time.tm_hour,
				     RTC_HRS_24_BIN_MASK,
				     RTC_HRS_24_BCD_MASK);
	mday	= ds1685_rtc_bin2bcd(rtc, alrm->time.tm_mday,
				     RTC_MDAY_BIN_MASK,
				     RTC_MDAY_BCD_MASK);

	/* Check the month date for validity. */
	ret = ds1685_rtc_check_mday(rtc, mday);
	if (ret)
		return ret;

	/*
	 * Check the three alarm bytes.
	 *
	 * The Linux RTC system doesn't support the "don't care" capability
	 * of this RTC chip because rtc_valid_tm tries to validate every
	 * field, and we only support four fields.  We put the support
	 * here anyways for the future.
	 */
	if (unlikely(seconds >= 0xc0))
		seconds = 0xff;

	if (unlikely(minutes >= 0xc0))
		minutes = 0xff;

	if (unlikely(hours >= 0xc0))
		hours = 0xff;

	alrm->time.tm_mon	= -1;
	alrm->time.tm_year	= -1;
	alrm->time.tm_wday	= -1;
	alrm->time.tm_yday	= -1;
	alrm->time.tm_isdst	= -1;

	/* Disable the alarm interrupt first. */
	ds1685_rtc_begin_data_access(rtc);
	ctrlb = rtc->read(rtc, RTC_CTRL_B);
	rtc->write(rtc, RTC_CTRL_B, (ctrlb & ~(RTC_CTRL_B_AIE)));

	/* Read ctrlc to clear RTC_CTRL_C_AF. */
	rtc->read(rtc, RTC_CTRL_C);

	/*
	 * Set the data mode to use and store the time values in the
	 * RTC registers.
	 */
	ctrlb = rtc->read(rtc, RTC_CTRL_B);
	if (rtc->bcd_mode)
		ctrlb &= ~(RTC_CTRL_B_DM);
	else
		ctrlb |= RTC_CTRL_B_DM;
	rtc->write(rtc, RTC_CTRL_B, ctrlb);
	rtc->write(rtc, RTC_SECS_ALARM, seconds);
	rtc->write(rtc, RTC_MINS_ALARM, minutes);
	rtc->write(rtc, RTC_HRS_ALARM, hours);
	rtc->write(rtc, RTC_MDAY_ALARM, mday);

	/* Re-enable the alarm if needed. */
	if (alrm->enabled) {
		ctrlb = rtc->read(rtc, RTC_CTRL_B);
		ctrlb |= RTC_CTRL_B_AIE;
		rtc->write(rtc, RTC_CTRL_B, ctrlb);
	}

	/* Done! */
	ds1685_rtc_end_data_access(rtc);

	return 0;
}