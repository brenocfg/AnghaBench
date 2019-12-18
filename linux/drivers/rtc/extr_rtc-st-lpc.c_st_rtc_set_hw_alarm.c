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
struct st_rtc {int /*<<< orphan*/  lock; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ LPC_LPA_LSB_OFF ; 
 scalar_t__ LPC_LPA_MSB_OFF ; 
 scalar_t__ LPC_LPA_START_OFF ; 
 scalar_t__ LPC_WDT_OFF ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void st_rtc_set_hw_alarm(struct st_rtc *rtc,
				unsigned long msb, unsigned long  lsb)
{
	unsigned long flags;

	spin_lock_irqsave(&rtc->lock, flags);

	writel_relaxed(1, rtc->ioaddr + LPC_WDT_OFF);

	writel_relaxed(msb, rtc->ioaddr + LPC_LPA_MSB_OFF);
	writel_relaxed(lsb, rtc->ioaddr + LPC_LPA_LSB_OFF);
	writel_relaxed(1, rtc->ioaddr + LPC_LPA_START_OFF);

	writel_relaxed(0, rtc->ioaddr + LPC_WDT_OFF);

	spin_unlock_irqrestore(&rtc->lock, flags);
}