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
struct velocity_rd_info {int /*<<< orphan*/ * skb; scalar_t__ skb_dma; } ;
struct TYPE_4__ {struct velocity_rd_info* info; int /*<<< orphan*/  buf_sz; struct rx_desc* ring; } ;
struct TYPE_3__ {int numrx; } ;
struct velocity_info {TYPE_2__ rx; int /*<<< orphan*/  dev; TYPE_1__ options; } ;
struct rx_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct velocity_rd_info*) ; 
 int /*<<< orphan*/  memset (struct rx_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void velocity_free_rd_ring(struct velocity_info *vptr)
{
	int i;

	if (vptr->rx.info == NULL)
		return;

	for (i = 0; i < vptr->options.numrx; i++) {
		struct velocity_rd_info *rd_info = &(vptr->rx.info[i]);
		struct rx_desc *rd = vptr->rx.ring + i;

		memset(rd, 0, sizeof(*rd));

		if (!rd_info->skb)
			continue;
		dma_unmap_single(vptr->dev, rd_info->skb_dma, vptr->rx.buf_sz,
				 DMA_FROM_DEVICE);
		rd_info->skb_dma = 0;

		dev_kfree_skb(rd_info->skb);
		rd_info->skb = NULL;
	}

	kfree(vptr->rx.info);
	vptr->rx.info = NULL;
}