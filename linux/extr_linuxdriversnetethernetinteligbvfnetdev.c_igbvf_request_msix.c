#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct igbvf_adapter {TYPE_3__* msix_entries; int /*<<< orphan*/  current_itr; TYPE_2__* rx_ring; TYPE_1__* tx_ring; struct net_device* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  itr_val; void* itr_register; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  itr_val; void* itr_register; } ;

/* Variables and functions */
 void* E1000_EITR (int) ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  igbvf_configure_msix (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_intr_msix_rx ; 
 int /*<<< orphan*/  igbvf_intr_msix_tx ; 
 int /*<<< orphan*/  igbvf_msix_other ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int igbvf_request_msix(struct igbvf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err = 0, vector = 0;

	if (strlen(netdev->name) < (IFNAMSIZ - 5)) {
		sprintf(adapter->tx_ring->name, "%s-tx-0", netdev->name);
		sprintf(adapter->rx_ring->name, "%s-rx-0", netdev->name);
	} else {
		memcpy(adapter->tx_ring->name, netdev->name, IFNAMSIZ);
		memcpy(adapter->rx_ring->name, netdev->name, IFNAMSIZ);
	}

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_intr_msix_tx, 0, adapter->tx_ring->name,
			  netdev);
	if (err)
		goto out;

	adapter->tx_ring->itr_register = E1000_EITR(vector);
	adapter->tx_ring->itr_val = adapter->current_itr;
	vector++;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_intr_msix_rx, 0, adapter->rx_ring->name,
			  netdev);
	if (err)
		goto out;

	adapter->rx_ring->itr_register = E1000_EITR(vector);
	adapter->rx_ring->itr_val = adapter->current_itr;
	vector++;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_msix_other, 0, netdev->name, netdev);
	if (err)
		goto out;

	igbvf_configure_msix(adapter);
	return 0;
out:
	return err;
}