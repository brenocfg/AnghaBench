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
struct net_device {int dummy; } ;
struct i40evf_adapter {int num_active_queues; struct i40e_ring* rx_rings; int /*<<< orphan*/  aq_required; struct net_device* netdev; } ;
struct i40e_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40EVF_FLAG_AQ_CONFIGURE_QUEUES ; 
 int /*<<< orphan*/  I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int /*<<< orphan*/  i40evf_alloc_rx_buffers (struct i40e_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_configure_rx (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_configure_tx (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_set_rx_mode (struct net_device*) ; 

__attribute__((used)) static void i40evf_configure(struct i40evf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int i;

	i40evf_set_rx_mode(netdev);

	i40evf_configure_tx(adapter);
	i40evf_configure_rx(adapter);
	adapter->aq_required |= I40EVF_FLAG_AQ_CONFIGURE_QUEUES;

	for (i = 0; i < adapter->num_active_queues; i++) {
		struct i40e_ring *ring = &adapter->rx_rings[i];

		i40evf_alloc_rx_buffers(ring, I40E_DESC_UNUSED(ring));
	}
}