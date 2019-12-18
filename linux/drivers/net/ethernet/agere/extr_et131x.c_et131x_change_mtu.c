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
struct net_device {int mtu; int /*<<< orphan*/  dev_addr; } ;
struct et131x_adapter {int registry_jumbo_packet; int /*<<< orphan*/  addr; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int et131x_adapter_memory_alloc (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_adapter_memory_free (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_disable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  et131x_enable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  et131x_hwaddr_init (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int et131x_change_mtu(struct net_device *netdev, int new_mtu)
{
	int result = 0;
	struct et131x_adapter *adapter = netdev_priv(netdev);

	et131x_disable_txrx(netdev);

	netdev->mtu = new_mtu;

	et131x_adapter_memory_free(adapter);

	/* Set the config parameter for Jumbo Packet support */
	adapter->registry_jumbo_packet = new_mtu + 14;
	et131x_soft_reset(adapter);

	result = et131x_adapter_memory_alloc(adapter);
	if (result != 0) {
		dev_warn(&adapter->pdev->dev,
			 "Change MTU failed; couldn't re-alloc DMA memory\n");
		return result;
	}

	et131x_init_send(adapter);
	et131x_hwaddr_init(adapter);
	ether_addr_copy(netdev->dev_addr, adapter->addr);

	/* Init the device with the new settings */
	et131x_adapter_setup(adapter);
	et131x_enable_txrx(netdev);

	return result;
}