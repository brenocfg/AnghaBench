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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* tm_mon; void* tm_mday; } ;
struct rtc_wkalrm {TYPE_1__ time; } ;
struct device {int dummy; } ;
struct cdns_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CDNS_RTC_CALAR ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_D ; 
 int /*<<< orphan*/  CDNS_RTC_CAL_M ; 
 scalar_t__ CDNS_RTC_TIMAR ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bcd2bin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_rtc_reg2time (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct cdns_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int cdns_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct cdns_rtc *crtc = dev_get_drvdata(dev);
	u32 reg;

	reg = readl(crtc->regs + CDNS_RTC_TIMAR);
	cdns_rtc_reg2time(reg, &alarm->time);

	reg = readl(crtc->regs + CDNS_RTC_CALAR);
	alarm->time.tm_mday = bcd2bin(FIELD_GET(CDNS_RTC_CAL_D, reg));
	alarm->time.tm_mon  = bcd2bin(FIELD_GET(CDNS_RTC_CAL_M, reg)) - 1;

	return 0;
}