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
struct hsu_dma_desc {scalar_t__ active; scalar_t__ nents; int /*<<< orphan*/  status; int /*<<< orphan*/  vdesc; } ;
struct hsu_dma_chip {TYPE_1__* hsu; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct hsu_dma_chan {TYPE_2__ vchan; struct hsu_dma_desc* desc; } ;
struct TYPE_3__ {unsigned short nr_channels; struct hsu_dma_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int /*<<< orphan*/  DMA_ERROR ; 
 int HSU_CH_SR_CHE ; 
 int /*<<< orphan*/  hsu_dma_start_channel (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  hsu_dma_start_transfer (struct hsu_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 

int hsu_dma_do_irq(struct hsu_dma_chip *chip, unsigned short nr, u32 status)
{
	struct hsu_dma_chan *hsuc;
	struct hsu_dma_desc *desc;
	unsigned long flags;

	/* Sanity check */
	if (nr >= chip->hsu->nr_channels)
		return 0;

	hsuc = &chip->hsu->chan[nr];

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	desc = hsuc->desc;
	if (desc) {
		if (status & HSU_CH_SR_CHE) {
			desc->status = DMA_ERROR;
		} else if (desc->active < desc->nents) {
			hsu_dma_start_channel(hsuc);
		} else {
			vchan_cookie_complete(&desc->vdesc);
			desc->status = DMA_COMPLETE;
			hsu_dma_start_transfer(hsuc);
		}
	}
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	return 1;
}