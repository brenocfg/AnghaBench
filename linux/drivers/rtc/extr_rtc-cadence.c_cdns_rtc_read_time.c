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
struct rtc_time {int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct device {int dummy; } ;
struct cdns_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CDNS_RTC_CALR ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_C ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_D ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_DAY ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_M ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_Y ; 
 scalar_t__ CDNS_RTC_TIMR ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcd2bin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_rtc_get_enabled (struct cdns_rtc*) ; 
 int /*<<< orphan*/  cdns_rtc_reg2time (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  cdns_rtc_set_enabled (struct cdns_rtc*,int) ; 
 struct cdns_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int cdns_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct cdns_rtc *crtc = dev_get_drvdata(dev);
	u32 reg;

	/* If the RTC is disabled, assume the values are invalid */
	if (!cdns_rtc_get_enabled(crtc))
		return -EINVAL;

	cdns_rtc_set_enabled(crtc, false);

	reg = readl(crtc->regs + CDNS_RTC_TIMR);
	cdns_rtc_reg2time(reg, tm);

	reg = readl(crtc->regs + CDNS_RTC_CALR);
	tm->tm_mday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_D, reg));
	tm->tm_mon  = bcd2bin(FIELD_GET(CDNS_RTC_CAL_M, reg)) - 1;
	tm->tm_year = bcd2bin(FIELD_GET(CDNS_RTC_CAL_Y, reg))
		    + bcd2bin(FIELD_GET(CDNS_RTC_CAL_C, reg)) * 100 - 1900;
	tm->tm_wday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_DAY, reg)) - 1;

	cdns_rtc_set_enabled(crtc, true);
	return 0;
}