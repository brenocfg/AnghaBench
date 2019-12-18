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

/* Variables and functions */
 int /*<<< orphan*/  WDT_DC ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wd_heartbeat ; 
 int /*<<< orphan*/  wdt_ctr_load (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_ctr_mode (int,int) ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static void wdt_ping(void)
{
	unsigned long flags;
	spin_lock_irqsave(&wdt_lock, flags);
	/* Write a watchdog value */
	inb_p(WDT_DC);			/* Disable watchdog */
	wdt_ctr_mode(1, 2);		/* Re-Program CTR1 for Mode 2:
							Rate Generator */
	wdt_ctr_load(1, wd_heartbeat);	/* Heartbeat */
	outb_p(0, WDT_DC);		/* Enable watchdog */
	spin_unlock_irqrestore(&wdt_lock, flags);
}