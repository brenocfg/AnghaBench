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
struct dc_wdt {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TIMER_A_CONTROL ; 
 scalar_t__ TIMER_A_COUNT ; 
 int TIMER_A_ENABLE_COUNT ; 
 int TIMER_A_ENABLE_WATCHDOG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void dc_wdt_set(struct dc_wdt *wdt, u32 ticks)
{
	unsigned long flags;

	spin_lock_irqsave(&wdt->lock, flags);

	writel_relaxed(0, wdt->base + TIMER_A_CONTROL);
	writel_relaxed(ticks, wdt->base + TIMER_A_COUNT);
	writel_relaxed(TIMER_A_ENABLE_COUNT | TIMER_A_ENABLE_WATCHDOG,
		       wdt->base + TIMER_A_CONTROL);

	spin_unlock_irqrestore(&wdt->lock, flags);
}