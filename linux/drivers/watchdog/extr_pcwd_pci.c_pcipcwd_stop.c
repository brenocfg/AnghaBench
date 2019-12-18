#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  io_lock; scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ VERBOSE ; 
 int WD_PCI_WDIS ; 
 scalar_t__ debug ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 TYPE_1__ pcipcwd_private ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcipcwd_stop(void)
{
	int stat_reg;

	spin_lock(&pcipcwd_private.io_lock);
	outb_p(0xA5, pcipcwd_private.io_addr + 3);
	udelay(1000);

	outb_p(0xA5, pcipcwd_private.io_addr + 3);
	udelay(1000);

	stat_reg = inb_p(pcipcwd_private.io_addr + 2);
	spin_unlock(&pcipcwd_private.io_lock);

	if (!(stat_reg & WD_PCI_WDIS)) {
		pr_err("Card did not acknowledge disable attempt\n");
		return -1;
	}

	if (debug >= VERBOSE)
		pr_debug("Watchdog stopped\n");

	return 0;
}