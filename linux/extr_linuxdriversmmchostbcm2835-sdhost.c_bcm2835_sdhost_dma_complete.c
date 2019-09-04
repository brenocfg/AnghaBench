#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_data {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct bcm2835_host {int drain_offset; int drain_page; int /*<<< orphan*/  lock; struct mmc_data* data; scalar_t__ drain_words; TYPE_2__* dma_chan; int /*<<< orphan*/  dma_dir; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SDCMD ; 
 int /*<<< orphan*/  SDDATA ; 
 int /*<<< orphan*/  SDEDM ; 
 int /*<<< orphan*/  SDHSTS ; 
 int /*<<< orphan*/  bcm2835_sdhost_finish_data (struct bcm2835_host*) ; 
 struct mmc_data* bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  log_event (char*,struct mmc_data*,struct mmc_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_sdhost_dma_complete(void *param)
{
	struct bcm2835_host *host = param;
	struct mmc_data *data = host->data;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	log_event("DMA<", host->data, bcm2835_sdhost_read(host, SDHSTS));
	log_event("DMA ", bcm2835_sdhost_read(host, SDCMD),
		  bcm2835_sdhost_read(host, SDEDM));

	if (host->dma_chan) {
		dma_unmap_sg(host->dma_chan->device->dev,
			     data->sg, data->sg_len,
			     host->dma_dir);

		host->dma_chan = NULL;
	}

	if (host->drain_words) {
		void *page;
		u32 *buf;

		if (host->drain_offset & PAGE_MASK) {
			host->drain_page += host->drain_offset >> PAGE_SHIFT;
			host->drain_offset &= ~PAGE_MASK;
		}

		page = kmap_atomic(host->drain_page);
		buf = page + host->drain_offset;

		while (host->drain_words) {
			u32 edm = bcm2835_sdhost_read(host, SDEDM);
			if ((edm >> 4) & 0x1f)
				*(buf++) = bcm2835_sdhost_read(host,
							       SDDATA);
			host->drain_words--;
		}

		kunmap_atomic(page);
	}

	bcm2835_sdhost_finish_data(host);

	log_event("DMA>", host->data, 0);
	spin_unlock_irqrestore(&host->lock, flags);
}