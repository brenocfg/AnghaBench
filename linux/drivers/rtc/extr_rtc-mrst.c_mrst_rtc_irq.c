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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RTC_INTR_FLAGS ; 
 int RTC_IRQF ; 
 int RTC_IRQMASK ; 
 scalar_t__ is_intr (int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_update_irq (void*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vrtc_cmos_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mrst_rtc_irq(int irq, void *p)
{
	u8 irqstat;

	spin_lock(&rtc_lock);
	/* This read will clear all IRQ flags inside Reg C */
	irqstat = vrtc_cmos_read(RTC_INTR_FLAGS);
	spin_unlock(&rtc_lock);

	irqstat &= RTC_IRQMASK | RTC_IRQF;
	if (is_intr(irqstat)) {
		rtc_update_irq(p, 1, irqstat);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}