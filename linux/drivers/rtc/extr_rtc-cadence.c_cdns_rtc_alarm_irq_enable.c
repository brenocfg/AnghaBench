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
struct device {int dummy; } ;
struct cdns_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 int CDNS_RTC_AEI_ALRM ; 
 int CDNS_RTC_AEI_DATE ; 
 int CDNS_RTC_AEI_HOUR ; 
 int CDNS_RTC_AEI_MIN ; 
 int CDNS_RTC_AEI_MNTH ; 
 int CDNS_RTC_AEI_SEC ; 
 scalar_t__ CDNS_RTC_AENR ; 
 scalar_t__ CDNS_RTC_IDISR ; 
 scalar_t__ CDNS_RTC_IENR ; 
 struct cdns_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cdns_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct cdns_rtc *crtc = dev_get_drvdata(dev);

	if (enabled) {
		writel((CDNS_RTC_AEI_SEC | CDNS_RTC_AEI_MIN | CDNS_RTC_AEI_HOUR
			| CDNS_RTC_AEI_DATE | CDNS_RTC_AEI_MNTH),
		       crtc->regs + CDNS_RTC_AENR);
		writel(CDNS_RTC_AEI_ALRM, crtc->regs + CDNS_RTC_IENR);
	} else {
		writel(0, crtc->regs + CDNS_RTC_AENR);
		writel(CDNS_RTC_AEI_ALRM, crtc->regs + CDNS_RTC_IDISR);
	}

	return 0;
}