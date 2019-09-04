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
struct ata_host {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 unsigned int adma_intr_mmio (struct ata_host*) ; 
 unsigned int adma_intr_pkt (struct ata_host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t adma_intr(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	unsigned int handled = 0;

	VPRINTK("ENTER\n");

	spin_lock(&host->lock);
	handled  = adma_intr_pkt(host) | adma_intr_mmio(host);
	spin_unlock(&host->lock);

	VPRINTK("EXIT\n");

	return IRQ_RETVAL(handled);
}