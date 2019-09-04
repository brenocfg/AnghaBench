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
struct e1000_ring {struct e1000_adapter* adapter; } ;
struct e1000_buffer {scalar_t__ time_stamp; int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma; int /*<<< orphan*/  length; scalar_t__ mapped_as_page; } ;
struct e1000_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_put_txbuf(struct e1000_ring *tx_ring,
			    struct e1000_buffer *buffer_info,
			    bool drop)
{
	struct e1000_adapter *adapter = tx_ring->adapter;

	if (buffer_info->dma) {
		if (buffer_info->mapped_as_page)
			dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
		else
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_TO_DEVICE);
		buffer_info->dma = 0;
	}
	if (buffer_info->skb) {
		if (drop)
			dev_kfree_skb_any(buffer_info->skb);
		else
			dev_consume_skb_any(buffer_info->skb);
		buffer_info->skb = NULL;
	}
	buffer_info->time_stamp = 0;
}