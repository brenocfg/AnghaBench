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
struct at91wdt {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_SR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ wdt_read (struct at91wdt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wdt_interrupt(int irq, void *dev_id)
{
	struct at91wdt *wdt = (struct at91wdt *)dev_id;

	if (wdt_read(wdt, AT91_WDT_SR)) {
		pr_crit("at91sam9 WDT software reset\n");
		emergency_restart();
		pr_crit("Reboot didn't ?????\n");
	}

	return IRQ_HANDLED;
}