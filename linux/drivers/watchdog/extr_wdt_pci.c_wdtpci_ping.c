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
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wd_heartbeat ; 
 int /*<<< orphan*/  wdtpci_ctr_load (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdtpci_ctr_mode (int,int) ; 
 int /*<<< orphan*/  wdtpci_lock ; 

__attribute__((used)) static int wdtpci_ping(void)
{
	unsigned long flags;

	spin_lock_irqsave(&wdtpci_lock, flags);
	/* Write a watchdog value */
	inb(WDT_DC);			/* Disable watchdog */
	udelay(8);
	wdtpci_ctr_mode(1, 2);		/* Re-Program CTR1 for Mode 2:
							Rate Generator */
	wdtpci_ctr_load(1, wd_heartbeat);/* Heartbeat */
	outb(0, WDT_DC);		/* Enable watchdog */
	udelay(8);
	spin_unlock_irqrestore(&wdtpci_lock, flags);
	return 0;
}