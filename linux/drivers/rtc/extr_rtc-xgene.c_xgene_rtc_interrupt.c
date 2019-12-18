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
struct xgene_rtc_dev {int /*<<< orphan*/  rtc; scalar_t__ csr_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 scalar_t__ RTC_EOI ; 
 int RTC_IRQF ; 
 scalar_t__ RTC_STAT ; 
 int RTC_STAT_BIT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t xgene_rtc_interrupt(int irq, void *id)
{
	struct xgene_rtc_dev *pdata = id;

	/* Check if interrupt asserted */
	if (!(readl(pdata->csr_base + RTC_STAT) & RTC_STAT_BIT))
		return IRQ_NONE;

	/* Clear interrupt */
	readl(pdata->csr_base + RTC_EOI);

	rtc_update_irq(pdata->rtc, 1, RTC_IRQF | RTC_AF);

	return IRQ_HANDLED;
}