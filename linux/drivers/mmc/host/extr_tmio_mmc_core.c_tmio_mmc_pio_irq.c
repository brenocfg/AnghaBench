#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {int sg_off; TYPE_1__* sg_ptr; scalar_t__ dma_on; struct mmc_data* data; } ;
struct mmc_data {unsigned int blksz; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {unsigned int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 void* tmio_mmc_kmap_atomic (TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  tmio_mmc_kunmap_atomic (TYPE_1__*,unsigned long*,void*) ; 
 int /*<<< orphan*/  tmio_mmc_next_sg (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_transfer_data (struct tmio_mmc_host*,unsigned short*,unsigned int) ; 

__attribute__((used)) static void tmio_mmc_pio_irq(struct tmio_mmc_host *host)
{
	struct mmc_data *data = host->data;
	void *sg_virt;
	unsigned short *buf;
	unsigned int count;
	unsigned long flags;

	if (host->dma_on) {
		pr_err("PIO IRQ in DMA mode!\n");
		return;
	} else if (!data) {
		pr_debug("Spurious PIO IRQ\n");
		return;
	}

	sg_virt = tmio_mmc_kmap_atomic(host->sg_ptr, &flags);
	buf = (unsigned short *)(sg_virt + host->sg_off);

	count = host->sg_ptr->length - host->sg_off;
	if (count > data->blksz)
		count = data->blksz;

	pr_debug("count: %08x offset: %08x flags %08x\n",
		 count, host->sg_off, data->flags);

	/* Transfer the data */
	tmio_mmc_transfer_data(host, buf, count);

	host->sg_off += count;

	tmio_mmc_kunmap_atomic(host->sg_ptr, &flags, sg_virt);

	if (host->sg_off == host->sg_ptr->length)
		tmio_mmc_next_sg(host);
}