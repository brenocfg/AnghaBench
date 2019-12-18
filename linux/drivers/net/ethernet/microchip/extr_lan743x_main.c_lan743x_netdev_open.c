#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; TYPE_1__* rx; int /*<<< orphan*/ * tx; } ;
struct TYPE_3__ {scalar_t__ ring_cpu_ptr; } ;

/* Variables and functions */
 int LAN743X_USED_RX_CHANNELS ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  lan743x_intr_close (struct lan743x_adapter*) ; 
 int lan743x_intr_open (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_mac_close (struct lan743x_adapter*) ; 
 int lan743x_mac_open (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_phy_close (struct lan743x_adapter*) ; 
 int lan743x_phy_open (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ptp_close (struct lan743x_adapter*) ; 
 int lan743x_ptp_open (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_rfe_open (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_rx_close (TYPE_1__*) ; 
 int lan743x_rx_open (TYPE_1__*) ; 
 int lan743x_tx_open (int /*<<< orphan*/ *) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int lan743x_netdev_open(struct net_device *netdev)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int index;
	int ret;

	ret = lan743x_intr_open(adapter);
	if (ret)
		goto return_error;

	ret = lan743x_mac_open(adapter);
	if (ret)
		goto close_intr;

	ret = lan743x_phy_open(adapter);
	if (ret)
		goto close_mac;

	ret = lan743x_ptp_open(adapter);
	if (ret)
		goto close_phy;

	lan743x_rfe_open(adapter);

	for (index = 0; index < LAN743X_USED_RX_CHANNELS; index++) {
		ret = lan743x_rx_open(&adapter->rx[index]);
		if (ret)
			goto close_rx;
	}

	ret = lan743x_tx_open(&adapter->tx[0]);
	if (ret)
		goto close_rx;

	return 0;

close_rx:
	for (index = 0; index < LAN743X_USED_RX_CHANNELS; index++) {
		if (adapter->rx[index].ring_cpu_ptr)
			lan743x_rx_close(&adapter->rx[index]);
	}
	lan743x_ptp_close(adapter);

close_phy:
	lan743x_phy_close(adapter);

close_mac:
	lan743x_mac_close(adapter);

close_intr:
	lan743x_intr_close(adapter);

return_error:
	netif_warn(adapter, ifup, adapter->netdev,
		   "Error opening LAN743x\n");
	return ret;
}