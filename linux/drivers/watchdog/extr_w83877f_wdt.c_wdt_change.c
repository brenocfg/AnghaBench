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
 int DISABLE_W83877F ; 
 int ENABLE_W83877F ; 
 scalar_t__ ENABLE_W83877F_PORT ; 
 int /*<<< orphan*/  WDT_PING ; 
 int WDT_REGISTER ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wdt_spinlock ; 

__attribute__((used)) static void wdt_change(int writeval)
{
	unsigned long flags;
	spin_lock_irqsave(&wdt_spinlock, flags);

	/* buy some time */
	inb_p(WDT_PING);

	/* make W83877F available */
	outb_p(ENABLE_W83877F,  ENABLE_W83877F_PORT);
	outb_p(ENABLE_W83877F,  ENABLE_W83877F_PORT);

	/* enable watchdog */
	outb_p(WDT_REGISTER,    ENABLE_W83877F_PORT);
	outb_p(writeval,        ENABLE_W83877F_PORT+1);

	/* lock the W8387FF away */
	outb_p(DISABLE_W83877F, ENABLE_W83877F_PORT);

	spin_unlock_irqrestore(&wdt_spinlock, flags);
}