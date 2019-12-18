#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct velocity_rd_info {int /*<<< orphan*/  skb_dma; TYPE_2__* skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_sz; struct velocity_rd_info* info; struct rx_desc* ring; } ;
struct velocity_info {TYPE_1__ rx; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; } ;
struct rx_desc {int size; scalar_t__ pa_high; int /*<<< orphan*/  pa_low; int /*<<< orphan*/  rdesc0; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int RX_INTEN ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_2__*,int) ; 

__attribute__((used)) static int velocity_alloc_rx_buf(struct velocity_info *vptr, int idx)
{
	struct rx_desc *rd = &(vptr->rx.ring[idx]);
	struct velocity_rd_info *rd_info = &(vptr->rx.info[idx]);

	rd_info->skb = netdev_alloc_skb(vptr->netdev, vptr->rx.buf_sz + 64);
	if (rd_info->skb == NULL)
		return -ENOMEM;

	/*
	 *	Do the gymnastics to get the buffer head for data at
	 *	64byte alignment.
	 */
	skb_reserve(rd_info->skb,
			64 - ((unsigned long) rd_info->skb->data & 63));
	rd_info->skb_dma = dma_map_single(vptr->dev, rd_info->skb->data,
					vptr->rx.buf_sz, DMA_FROM_DEVICE);

	/*
	 *	Fill in the descriptor to match
	 */

	*((u32 *) & (rd->rdesc0)) = 0;
	rd->size = cpu_to_le16(vptr->rx.buf_sz) | RX_INTEN;
	rd->pa_low = cpu_to_le32(rd_info->skb_dma);
	rd->pa_high = 0;
	return 0;
}