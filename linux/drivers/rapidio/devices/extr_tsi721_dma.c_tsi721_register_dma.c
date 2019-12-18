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
struct TYPE_6__ {int chancnt; int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_prep_slave_sg; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/ * dev; int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;
struct rio_mport {TYPE_3__ dma; } ;
struct tsi721_device {TYPE_2__* pdev; scalar_t__ regs; struct tsi721_bdma_chan* bdma; struct rio_mport mport; } ;
struct TYPE_4__ {int cookie; int chan_id; int /*<<< orphan*/  device_node; TYPE_3__* device; } ;
struct tsi721_bdma_chan {int id; int active; TYPE_1__ dchan; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  free_list; int /*<<< orphan*/  queue; int /*<<< orphan*/ * active_tx; int /*<<< orphan*/  lock; scalar_t__ regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIVATE ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TSI721_DMACH_MAINT ; 
 scalar_t__ TSI721_DMAC_BASE (int) ; 
 int TSI721_DMA_MAXCH ; 
 int dma_async_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int dma_sel ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tsi721_alloc_chan_resources ; 
 int /*<<< orphan*/  tsi721_dma_tasklet ; 
 int /*<<< orphan*/  tsi721_free_chan_resources ; 
 int /*<<< orphan*/  tsi721_issue_pending ; 
 int /*<<< orphan*/  tsi721_prep_rio_sg ; 
 int /*<<< orphan*/  tsi721_terminate_all ; 
 int /*<<< orphan*/  tsi721_tx_status ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*) ; 

int tsi721_register_dma(struct tsi721_device *priv)
{
	int i;
	int nr_channels = 0;
	int err;
	struct rio_mport *mport = &priv->mport;

	INIT_LIST_HEAD(&mport->dma.channels);

	for (i = 0; i < TSI721_DMA_MAXCH; i++) {
		struct tsi721_bdma_chan *bdma_chan = &priv->bdma[i];

		if ((i == TSI721_DMACH_MAINT) || (dma_sel & (1 << i)) == 0)
			continue;

		bdma_chan->regs = priv->regs + TSI721_DMAC_BASE(i);

		bdma_chan->dchan.device = &mport->dma;
		bdma_chan->dchan.cookie = 1;
		bdma_chan->dchan.chan_id = i;
		bdma_chan->id = i;
		bdma_chan->active = false;

		spin_lock_init(&bdma_chan->lock);

		bdma_chan->active_tx = NULL;
		INIT_LIST_HEAD(&bdma_chan->queue);
		INIT_LIST_HEAD(&bdma_chan->free_list);

		tasklet_init(&bdma_chan->tasklet, tsi721_dma_tasklet,
			     (unsigned long)bdma_chan);
		list_add_tail(&bdma_chan->dchan.device_node,
			      &mport->dma.channels);
		nr_channels++;
	}

	mport->dma.chancnt = nr_channels;
	dma_cap_zero(mport->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, mport->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, mport->dma.cap_mask);

	mport->dma.dev = &priv->pdev->dev;
	mport->dma.device_alloc_chan_resources = tsi721_alloc_chan_resources;
	mport->dma.device_free_chan_resources = tsi721_free_chan_resources;
	mport->dma.device_tx_status = tsi721_tx_status;
	mport->dma.device_issue_pending = tsi721_issue_pending;
	mport->dma.device_prep_slave_sg = tsi721_prep_rio_sg;
	mport->dma.device_terminate_all = tsi721_terminate_all;

	err = dma_async_device_register(&mport->dma);
	if (err)
		tsi_err(&priv->pdev->dev, "Failed to register DMA device");

	return err;
}