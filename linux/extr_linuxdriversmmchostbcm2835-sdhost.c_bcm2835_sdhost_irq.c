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
struct bcm2835_host {int hcfg; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SDHCFG_DATA_IRPT_EN ; 
 int /*<<< orphan*/  SDHSTS ; 
 int SDHSTS_BLOCK_IRPT ; 
 int SDHSTS_BUSY_IRPT ; 
 int SDHSTS_DATA_FLAG ; 
 int SDHSTS_SDIO_IRPT ; 
 int /*<<< orphan*/  bcm2835_sdhost_block_irq (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_sdhost_busy_irq (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_sdhost_data_irq (struct bcm2835_host*,int) ; 
 int bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_event (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bcm2835_sdhost_irq(int irq, void *dev_id)
{
	irqreturn_t result = IRQ_NONE;
	struct bcm2835_host *host = dev_id;
	u32 intmask;

	spin_lock(&host->lock);

	intmask = bcm2835_sdhost_read(host, SDHSTS);
	log_event("IRQ<", intmask, 0);

	bcm2835_sdhost_write(host,
			     SDHSTS_BUSY_IRPT |
			     SDHSTS_BLOCK_IRPT |
			     SDHSTS_SDIO_IRPT |
			     SDHSTS_DATA_FLAG,
			     SDHSTS);

	if (intmask & SDHSTS_BLOCK_IRPT) {
		bcm2835_sdhost_block_irq(host, intmask);
		result = IRQ_HANDLED;
	}

	if (intmask & SDHSTS_BUSY_IRPT) {
		bcm2835_sdhost_busy_irq(host, intmask);
		result = IRQ_HANDLED;
	}

	/* There is no true data interrupt status bit, so it is
	   necessary to qualify the data flag with the interrupt
	   enable bit */
	if ((intmask & SDHSTS_DATA_FLAG) &&
	    (host->hcfg & SDHCFG_DATA_IRPT_EN)) {
		bcm2835_sdhost_data_irq(host, intmask);
		result = IRQ_HANDLED;
	}

	mmiowb();

	log_event("IRQ>", bcm2835_sdhost_read(host, SDHSTS), 0);
	spin_unlock(&host->lock);

	return result;
}