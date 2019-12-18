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
struct net_device {int mtu; } ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int ena_com_set_dev_mtu (int /*<<< orphan*/ ,int) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  update_rx_ring_mtu (struct ena_adapter*,int) ; 

__attribute__((used)) static int ena_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ena_adapter *adapter = netdev_priv(dev);
	int ret;

	ret = ena_com_set_dev_mtu(adapter->ena_dev, new_mtu);
	if (!ret) {
		netif_dbg(adapter, drv, dev, "set MTU to %d\n", new_mtu);
		update_rx_ring_mtu(adapter, new_mtu);
		dev->mtu = new_mtu;
	} else {
		netif_err(adapter, drv, dev, "Failed to set MTU to %d\n",
			  new_mtu);
	}

	return ret;
}