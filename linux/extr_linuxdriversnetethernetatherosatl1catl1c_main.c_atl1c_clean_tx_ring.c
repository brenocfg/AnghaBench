#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u16 ;
struct pci_dev {int dummy; } ;
struct atl1c_tpd_ring {size_t count; scalar_t__ next_to_use; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  desc; struct atl1c_buffer* buffer_info; } ;
struct atl1c_tpd_desc {int dummy; } ;
struct atl1c_buffer {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  netdev; struct pci_dev* pdev; struct atl1c_tpd_ring* tpd_ring; } ;
typedef  enum atl1c_trans_queue { ____Placeholder_atl1c_trans_queue } atl1c_trans_queue ;

/* Variables and functions */
 int /*<<< orphan*/  atl1c_clean_buffer (struct pci_dev*,struct atl1c_buffer*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1c_clean_tx_ring(struct atl1c_adapter *adapter,
				enum atl1c_trans_queue type)
{
	struct atl1c_tpd_ring *tpd_ring = &adapter->tpd_ring[type];
	struct atl1c_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	u16 index, ring_count;

	ring_count = tpd_ring->count;
	for (index = 0; index < ring_count; index++) {
		buffer_info = &tpd_ring->buffer_info[index];
		atl1c_clean_buffer(pdev, buffer_info);
	}

	netdev_reset_queue(adapter->netdev);

	/* Zero out Tx-buffers */
	memset(tpd_ring->desc, 0, sizeof(struct atl1c_tpd_desc) *
		ring_count);
	atomic_set(&tpd_ring->next_to_clean, 0);
	tpd_ring->next_to_use = 0;
}