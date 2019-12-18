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
struct qlcnic_host_tx_ring {int irq; struct qlcnic_adapter* adapter; int /*<<< orphan*/  tx_clean_lock; struct qlcnic_cmd_buffer* cmd_buf_arr; int /*<<< orphan*/  txq; int /*<<< orphan*/  num_desc; } ;
struct qlcnic_cmd_buffer {int dummy; } ;
struct qlcnic_adapter {int drv_tx_rings; int flags; int drv_sds_rings; TYPE_1__* msix_entries; struct qlcnic_host_tx_ring* tx_ring; int /*<<< orphan*/  num_txd; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int vector; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  TX_BUFF_RINGSIZE (struct qlcnic_host_tx_ring*) ; 
 struct qlcnic_host_tx_ring* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_tx_rings (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct qlcnic_cmd_buffer* vzalloc (int /*<<< orphan*/ ) ; 

int qlcnic_alloc_tx_rings(struct qlcnic_adapter *adapter,
			  struct net_device *netdev)
{
	int ring, vector, index;
	struct qlcnic_host_tx_ring *tx_ring;
	struct qlcnic_cmd_buffer *cmd_buf_arr;

	tx_ring = kcalloc(adapter->drv_tx_rings,
			  sizeof(struct qlcnic_host_tx_ring), GFP_KERNEL);
	if (tx_ring == NULL)
		return -ENOMEM;

	adapter->tx_ring = tx_ring;

	for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
		tx_ring = &adapter->tx_ring[ring];
		tx_ring->num_desc = adapter->num_txd;
		tx_ring->txq = netdev_get_tx_queue(netdev, ring);
		cmd_buf_arr = vzalloc(TX_BUFF_RINGSIZE(tx_ring));
		if (cmd_buf_arr == NULL) {
			qlcnic_free_tx_rings(adapter);
			return -ENOMEM;
		}
		tx_ring->cmd_buf_arr = cmd_buf_arr;
		spin_lock_init(&tx_ring->tx_clean_lock);
	}

	if (qlcnic_83xx_check(adapter) ||
	    (qlcnic_82xx_check(adapter) && qlcnic_check_multi_tx(adapter))) {
		for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
			tx_ring = &adapter->tx_ring[ring];
			tx_ring->adapter = adapter;
			if (adapter->flags & QLCNIC_MSIX_ENABLED) {
				index = adapter->drv_sds_rings + ring;
				vector = adapter->msix_entries[index].vector;
				tx_ring->irq = vector;
			}
		}
	}

	return 0;
}