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
struct npcm_wdt {int /*<<< orphan*/  wdd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  watchdog_notify_pretimeout (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t npcm_wdt_interrupt(int irq, void *data)
{
	struct npcm_wdt *wdt = data;

	watchdog_notify_pretimeout(&wdt->wdd);

	return IRQ_HANDLED;
}