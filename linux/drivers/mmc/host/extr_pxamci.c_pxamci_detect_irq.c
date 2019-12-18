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
struct pxamci_host {int /*<<< orphan*/  detect_delay_ms; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mmc_detect_change (void*,int /*<<< orphan*/ ) ; 
 struct pxamci_host* mmc_priv (void*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pxamci_detect_irq(int irq, void *devid)
{
	struct pxamci_host *host = mmc_priv(devid);

	mmc_detect_change(devid, msecs_to_jiffies(host->detect_delay_ms));
	return IRQ_HANDLED;
}