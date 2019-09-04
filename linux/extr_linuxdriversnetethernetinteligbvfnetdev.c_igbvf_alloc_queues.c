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
struct net_device {int dummy; } ;
struct igbvf_ring {int dummy; } ;
struct igbvf_adapter {TYPE_1__* rx_ring; void* tx_ring; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  igbvf_poll ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igbvf_alloc_queues(struct igbvf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	adapter->tx_ring = kzalloc(sizeof(struct igbvf_ring), GFP_KERNEL);
	if (!adapter->tx_ring)
		return -ENOMEM;

	adapter->rx_ring = kzalloc(sizeof(struct igbvf_ring), GFP_KERNEL);
	if (!adapter->rx_ring) {
		kfree(adapter->tx_ring);
		return -ENOMEM;
	}

	netif_napi_add(netdev, &adapter->rx_ring->napi, igbvf_poll, 64);

	return 0;
}