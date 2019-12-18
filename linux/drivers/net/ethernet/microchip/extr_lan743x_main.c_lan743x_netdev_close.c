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
struct lan743x_adapter {int /*<<< orphan*/ * rx; int /*<<< orphan*/ * tx; } ;

/* Variables and functions */
 int LAN743X_USED_RX_CHANNELS ; 
 int /*<<< orphan*/  lan743x_intr_close (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_mac_close (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_phy_close (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ptp_close (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_rx_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lan743x_tx_close (int /*<<< orphan*/ *) ; 
 struct lan743x_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int lan743x_netdev_close(struct net_device *netdev)
{
	struct lan743x_adapter *adapter = netdev_priv(netdev);
	int index;

	lan743x_tx_close(&adapter->tx[0]);

	for (index = 0; index < LAN743X_USED_RX_CHANNELS; index++)
		lan743x_rx_close(&adapter->rx[index]);

	lan743x_ptp_close(adapter);

	lan743x_phy_close(adapter);

	lan743x_mac_close(adapter);

	lan743x_intr_close(adapter);

	return 0;
}