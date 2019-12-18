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
struct cdns_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ CDNS_RTC_CTLR ; 
 int CDNS_RTC_CTLR_TIME_CAL ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool cdns_rtc_get_enabled(struct cdns_rtc *crtc)
{
	return !(readl(crtc->regs + CDNS_RTC_CTLR) & CDNS_RTC_CTLR_TIME_CAL);
}