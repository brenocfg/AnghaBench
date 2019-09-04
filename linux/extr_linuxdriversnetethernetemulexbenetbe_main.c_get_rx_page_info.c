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
typedef  size_t u32 ;
struct be_rx_page_info {int last_frag; int /*<<< orphan*/  page; } ;
struct be_queue_info {size_t tail; int /*<<< orphan*/  used; } ;
struct be_rx_obj {struct be_rx_page_info* page_info_tbl; struct be_queue_info q; struct be_adapter* adapter; } ;
struct be_adapter {TYPE_1__* pdev; int /*<<< orphan*/  big_page_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct be_rx_page_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_tail_inc (struct be_queue_info*) ; 
 int /*<<< orphan*/  rx_frag_size ; 

__attribute__((used)) static struct be_rx_page_info *get_rx_page_info(struct be_rx_obj *rxo)
{
	struct be_adapter *adapter = rxo->adapter;
	struct be_rx_page_info *rx_page_info;
	struct be_queue_info *rxq = &rxo->q;
	u32 frag_idx = rxq->tail;

	rx_page_info = &rxo->page_info_tbl[frag_idx];
	BUG_ON(!rx_page_info->page);

	if (rx_page_info->last_frag) {
		dma_unmap_page(&adapter->pdev->dev,
			       dma_unmap_addr(rx_page_info, bus),
			       adapter->big_page_size, DMA_FROM_DEVICE);
		rx_page_info->last_frag = false;
	} else {
		dma_sync_single_for_cpu(&adapter->pdev->dev,
					dma_unmap_addr(rx_page_info, bus),
					rx_frag_size, DMA_FROM_DEVICE);
	}

	queue_tail_inc(rxq);
	atomic_dec(&rxq->used);
	return rx_page_info;
}