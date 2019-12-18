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
typedef  int u32 ;
struct vt8500_rtc {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; scalar_t__ regbase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 scalar_t__ VT8500_RTC_IS ; 
 int VT8500_RTC_IS_ALARM ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vt8500_rtc_irq(int irq, void *dev_id)
{
	struct vt8500_rtc *vt8500_rtc = dev_id;
	u32 isr;
	unsigned long events = 0;

	spin_lock(&vt8500_rtc->lock);

	/* clear interrupt sources */
	isr = readl(vt8500_rtc->regbase + VT8500_RTC_IS);
	writel(isr, vt8500_rtc->regbase + VT8500_RTC_IS);

	spin_unlock(&vt8500_rtc->lock);

	if (isr & VT8500_RTC_IS_ALARM)
		events |= RTC_AF | RTC_IRQF;

	rtc_update_irq(vt8500_rtc->rtc, 1, events);

	return IRQ_HANDLED;
}