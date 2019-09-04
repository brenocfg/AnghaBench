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
struct pch_gbe_buffer {int mapped; int /*<<< orphan*/ * skb; int /*<<< orphan*/  length; int /*<<< orphan*/  dma; } ;
struct pch_gbe_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_gbe_unmap_and_free_rx_resource(
					struct pch_gbe_adapter *adapter,
					struct pch_gbe_buffer *buffer_info)
{
	if (buffer_info->mapped) {
		dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
				 buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->mapped = false;
	}
	if (buffer_info->skb) {
		dev_kfree_skb_any(buffer_info->skb);
		buffer_info->skb = NULL;
	}
}