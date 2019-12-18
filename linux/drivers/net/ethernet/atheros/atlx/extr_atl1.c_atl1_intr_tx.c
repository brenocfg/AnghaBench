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
typedef  size_t u16 ;
struct atl1_tpd_ring {size_t count; int /*<<< orphan*/  next_to_clean; struct atl1_buffer* buffer_info; } ;
struct atl1_buffer {int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {TYPE_1__* cmb; } ;
struct atl1_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  pdev; TYPE_2__ cmb; struct atl1_tpd_ring tpd_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  tpd_cons_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (int /*<<< orphan*/ *) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atl1_intr_tx(struct atl1_adapter *adapter)
{
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_buffer *buffer_info;
	u16 sw_tpd_next_to_clean;
	u16 cmb_tpd_next_to_clean;
	int count = 0;

	sw_tpd_next_to_clean = atomic_read(&tpd_ring->next_to_clean);
	cmb_tpd_next_to_clean = le16_to_cpu(adapter->cmb.cmb->tpd_cons_idx);

	while (cmb_tpd_next_to_clean != sw_tpd_next_to_clean) {
		buffer_info = &tpd_ring->buffer_info[sw_tpd_next_to_clean];
		if (buffer_info->dma) {
			pci_unmap_page(adapter->pdev, buffer_info->dma,
				       buffer_info->length, PCI_DMA_TODEVICE);
			buffer_info->dma = 0;
		}

		if (buffer_info->skb) {
			dev_consume_skb_irq(buffer_info->skb);
			buffer_info->skb = NULL;
		}

		if (++sw_tpd_next_to_clean == tpd_ring->count)
			sw_tpd_next_to_clean = 0;

		count++;
	}
	atomic_set(&tpd_ring->next_to_clean, sw_tpd_next_to_clean);

	if (netif_queue_stopped(adapter->netdev) &&
	    netif_carrier_ok(adapter->netdev))
		netif_wake_queue(adapter->netdev);

	return count;
}