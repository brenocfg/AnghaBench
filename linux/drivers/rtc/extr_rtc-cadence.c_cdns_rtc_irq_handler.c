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
struct cdns_rtc {int /*<<< orphan*/  rtc_dev; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CDNS_RTC_AEI_ALRM ; 
 scalar_t__ CDNS_RTC_EFLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 struct cdns_rtc* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t cdns_rtc_irq_handler(int irq, void *id)
{
	struct device *dev = id;
	struct cdns_rtc *crtc = dev_get_drvdata(dev);

	/* Reading the register clears it */
	if (!(readl(crtc->regs + CDNS_RTC_EFLR) & CDNS_RTC_AEI_ALRM))
		return IRQ_NONE;

	rtc_update_irq(crtc->rtc_dev, 1, RTC_IRQF | RTC_AF);
	return IRQ_HANDLED;
}