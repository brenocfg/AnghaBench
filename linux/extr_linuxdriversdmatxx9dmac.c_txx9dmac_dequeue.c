#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct txx9dmac_dev {int /*<<< orphan*/  descsize; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  phys; } ;
struct txx9dmac_desc {TYPE_1__ txd; int /*<<< orphan*/  desc_node; } ;
struct list_head {int dummy; } ;
struct txx9dmac_chan {int /*<<< orphan*/  chan; struct list_head queue; struct txx9dmac_dev* ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  chan2parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_write_CHAR (struct txx9dmac_chan*,struct txx9dmac_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  txx9dmac_chan_INTENT (struct txx9dmac_chan*) ; 
 struct txx9dmac_desc* txx9dmac_first_queued (struct txx9dmac_chan*) ; 
 struct txx9dmac_desc* txx9dmac_last_child (struct txx9dmac_desc*) ; 

__attribute__((used)) static void txx9dmac_dequeue(struct txx9dmac_chan *dc, struct list_head *list)
{
	struct txx9dmac_dev *ddev = dc->ddev;
	struct txx9dmac_desc *desc;
	struct txx9dmac_desc *prev = NULL;

	BUG_ON(!list_empty(list));
	do {
		desc = txx9dmac_first_queued(dc);
		if (prev) {
			desc_write_CHAR(dc, prev, desc->txd.phys);
			dma_sync_single_for_device(chan2parent(&dc->chan),
				prev->txd.phys, ddev->descsize,
				DMA_TO_DEVICE);
		}
		prev = txx9dmac_last_child(desc);
		list_move_tail(&desc->desc_node, list);
		/* Make chain-completion interrupt happen */
		if ((desc->txd.flags & DMA_PREP_INTERRUPT) &&
		    !txx9dmac_chan_INTENT(dc))
			break;
	} while (!list_empty(&dc->queue));
}