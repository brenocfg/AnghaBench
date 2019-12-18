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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static irqreturn_t eurwdt_interrupt(int irq, void *dev_id)
{
	pr_crit("timeout WDT timeout\n");

#ifdef ONLY_TESTING
	pr_crit("Would Reboot\n");
#else
	pr_crit("Initiating system reboot\n");
	emergency_restart();
#endif
	return IRQ_HANDLED;
}