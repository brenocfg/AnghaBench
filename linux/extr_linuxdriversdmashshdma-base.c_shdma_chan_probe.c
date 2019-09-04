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
struct TYPE_3__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  dev; } ;
struct shdma_dev {struct shdma_chan** schan; TYPE_1__ dma_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_node; TYPE_1__* device; } ;
struct shdma_chan {int id; TYPE_2__ dma_chan; int /*<<< orphan*/  ld_free; int /*<<< orphan*/  ld_queue; int /*<<< orphan*/  chan_lock; scalar_t__ max_xfer_len; int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SHDMA_PM_ESTABLISHED ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void shdma_chan_probe(struct shdma_dev *sdev,
			   struct shdma_chan *schan, int id)
{
	schan->pm_state = SHDMA_PM_ESTABLISHED;

	/* reference struct dma_device */
	schan->dma_chan.device = &sdev->dma_dev;
	dma_cookie_init(&schan->dma_chan);

	schan->dev = sdev->dma_dev.dev;
	schan->id = id;

	if (!schan->max_xfer_len)
		schan->max_xfer_len = PAGE_SIZE;

	spin_lock_init(&schan->chan_lock);

	/* Init descripter manage list */
	INIT_LIST_HEAD(&schan->ld_queue);
	INIT_LIST_HEAD(&schan->ld_free);

	/* Add the channel to DMA device channel list */
	list_add_tail(&schan->dma_chan.device_node,
			&sdev->dma_dev.channels);
	sdev->schan[id] = schan;
}