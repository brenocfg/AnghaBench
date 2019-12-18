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
struct iavf_ring {int dummy; } ;
struct iavf_adapter {int num_active_queues; struct iavf_ring* rx_rings; int /*<<< orphan*/  aq_required; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_DESC_UNUSED (struct iavf_ring*) ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_CONFIGURE_QUEUES ; 
 int /*<<< orphan*/  iavf_alloc_rx_buffers (struct iavf_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_configure_rx (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_configure_tx (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_set_rx_mode (struct net_device*) ; 

__attribute__((used)) static void iavf_configure(struct iavf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int i;

	iavf_set_rx_mode(netdev);

	iavf_configure_tx(adapter);
	iavf_configure_rx(adapter);
	adapter->aq_required |= IAVF_FLAG_AQ_CONFIGURE_QUEUES;

	for (i = 0; i < adapter->num_active_queues; i++) {
		struct iavf_ring *ring = &adapter->rx_rings[i];

		iavf_alloc_rx_buffers(ring, IAVF_DESC_UNUSED(ring));
	}
}