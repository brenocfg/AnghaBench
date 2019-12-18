#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_6__ {int flags; void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;} ;
struct tsi721_tx_desc {scalar_t__ sg_len; int /*<<< orphan*/  desc_node; TYPE_3__ txd; int /*<<< orphan*/  status; int /*<<< orphan*/  rio_addr; int /*<<< orphan*/  destid; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct tsi721_bdma_chan {scalar_t__ regs; int /*<<< orphan*/  lock; struct tsi721_tx_desc* active_tx; scalar_t__ active; int /*<<< orphan*/  free_list; int /*<<< orphan*/  id; TYPE_2__ dchan; scalar_t__ sts_rdptr; scalar_t__ wr_count_next; scalar_t__ wr_count; int /*<<< orphan*/  sts_size; scalar_t__ sts_phys; scalar_t__ bd_phys; } ;
typedef  int /*<<< orphan*/  (* dma_async_tx_callback ) (void*) ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int /*<<< orphan*/  DMA_COMPLETE ; 
 int /*<<< orphan*/  DMA_ERROR ; 
 int DMA_PREP_INTERRUPT ; 
 scalar_t__ TSI721_DMAC_CTL ; 
 int TSI721_DMAC_CTL_INIT ; 
 scalar_t__ TSI721_DMAC_DPTRH ; 
 scalar_t__ TSI721_DMAC_DPTRL ; 
 int TSI721_DMAC_DPTRL_MASK ; 
 scalar_t__ TSI721_DMAC_DSBH ; 
 scalar_t__ TSI721_DMAC_DSBL ; 
 int TSI721_DMAC_DSBL_MASK ; 
 scalar_t__ TSI721_DMAC_DSSZ ; 
 int TSI721_DMAC_DSSZ_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_DMAC_INT ; 
 scalar_t__ TSI721_DMAC_INTE ; 
 int TSI721_DMAC_INT_ALL ; 
 int TSI721_DMAC_INT_DONE ; 
 int TSI721_DMAC_INT_ERR ; 
 int TSI721_DMAC_INT_IOFDONE ; 
 int TSI721_DMAC_INT_STFULL ; 
 scalar_t__ TSI721_DMAC_STS ; 
 int TSI721_DMAC_STS_ABORT ; 
 int /*<<< orphan*/  dma_cookie_complete (TYPE_3__*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_advance_work (struct tsi721_bdma_chan*,struct tsi721_tx_desc*) ; 
 int /*<<< orphan*/  tsi721_clr_stat (struct tsi721_bdma_chan*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tsi721_dma_tasklet(unsigned long data)
{
	struct tsi721_bdma_chan *bdma_chan = (struct tsi721_bdma_chan *)data;
	u32 dmac_int, dmac_sts;

	dmac_int = ioread32(bdma_chan->regs + TSI721_DMAC_INT);
	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d_INT = 0x%x",
		  bdma_chan->id, dmac_int);
	/* Clear channel interrupts */
	iowrite32(dmac_int, bdma_chan->regs + TSI721_DMAC_INT);

	if (dmac_int & TSI721_DMAC_INT_ERR) {
		int i = 10000;
		struct tsi721_tx_desc *desc;

		desc = bdma_chan->active_tx;
		dmac_sts = ioread32(bdma_chan->regs + TSI721_DMAC_STS);
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d_STS = 0x%x did=%d raddr=0x%llx",
			bdma_chan->id, dmac_sts, desc->destid, desc->rio_addr);

		/* Re-initialize DMA channel if possible */

		if ((dmac_sts & TSI721_DMAC_STS_ABORT) == 0)
			goto err_out;

		tsi721_clr_stat(bdma_chan);

		spin_lock(&bdma_chan->lock);

		/* Put DMA channel into init state */
		iowrite32(TSI721_DMAC_CTL_INIT,
			  bdma_chan->regs + TSI721_DMAC_CTL);
		do {
			udelay(1);
			dmac_sts = ioread32(bdma_chan->regs + TSI721_DMAC_STS);
			i--;
		} while ((dmac_sts & TSI721_DMAC_STS_ABORT) && i);

		if (dmac_sts & TSI721_DMAC_STS_ABORT) {
			tsi_err(&bdma_chan->dchan.dev->device,
				"Failed to re-initiate DMAC%d",	bdma_chan->id);
			spin_unlock(&bdma_chan->lock);
			goto err_out;
		}

		/* Setup DMA descriptor pointers */
		iowrite32(((u64)bdma_chan->bd_phys >> 32),
			bdma_chan->regs + TSI721_DMAC_DPTRH);
		iowrite32(((u64)bdma_chan->bd_phys & TSI721_DMAC_DPTRL_MASK),
			bdma_chan->regs + TSI721_DMAC_DPTRL);

		/* Setup descriptor status FIFO */
		iowrite32(((u64)bdma_chan->sts_phys >> 32),
			bdma_chan->regs + TSI721_DMAC_DSBH);
		iowrite32(((u64)bdma_chan->sts_phys & TSI721_DMAC_DSBL_MASK),
			bdma_chan->regs + TSI721_DMAC_DSBL);
		iowrite32(TSI721_DMAC_DSSZ_SIZE(bdma_chan->sts_size),
			bdma_chan->regs + TSI721_DMAC_DSSZ);

		/* Clear interrupt bits */
		iowrite32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);

		ioread32(bdma_chan->regs + TSI721_DMAC_INT);

		bdma_chan->wr_count = bdma_chan->wr_count_next = 0;
		bdma_chan->sts_rdptr = 0;
		udelay(10);

		desc = bdma_chan->active_tx;
		desc->status = DMA_ERROR;
		dma_cookie_complete(&desc->txd);
		list_add(&desc->desc_node, &bdma_chan->free_list);
		bdma_chan->active_tx = NULL;
		if (bdma_chan->active)
			tsi721_advance_work(bdma_chan, NULL);
		spin_unlock(&bdma_chan->lock);
	}

	if (dmac_int & TSI721_DMAC_INT_STFULL) {
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d descriptor status FIFO is full",
			bdma_chan->id);
	}

	if (dmac_int & (TSI721_DMAC_INT_DONE | TSI721_DMAC_INT_IOFDONE)) {
		struct tsi721_tx_desc *desc;

		tsi721_clr_stat(bdma_chan);
		spin_lock(&bdma_chan->lock);
		desc = bdma_chan->active_tx;

		if (desc->sg_len == 0) {
			dma_async_tx_callback callback = NULL;
			void *param = NULL;

			desc->status = DMA_COMPLETE;
			dma_cookie_complete(&desc->txd);
			if (desc->txd.flags & DMA_PREP_INTERRUPT) {
				callback = desc->txd.callback;
				param = desc->txd.callback_param;
			}
			list_add(&desc->desc_node, &bdma_chan->free_list);
			bdma_chan->active_tx = NULL;
			if (bdma_chan->active)
				tsi721_advance_work(bdma_chan, NULL);
			spin_unlock(&bdma_chan->lock);
			if (callback)
				callback(param);
		} else {
			if (bdma_chan->active)
				tsi721_advance_work(bdma_chan,
						    bdma_chan->active_tx);
			spin_unlock(&bdma_chan->lock);
		}
	}
err_out:
	/* Re-Enable BDMA channel interrupts */
	iowrite32(TSI721_DMAC_INT_ALL, bdma_chan->regs + TSI721_DMAC_INTE);
}