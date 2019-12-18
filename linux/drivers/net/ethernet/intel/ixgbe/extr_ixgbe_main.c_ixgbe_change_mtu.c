#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; } ;
struct ixgbe_ring {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int num_rx_queues; int flags; TYPE_2__ hw; struct ixgbe_ring** rx_ring; scalar_t__ xdp_prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_reinit_locked (struct ixgbe_adapter*) ; 
 int ixgbe_rx_bufsz (struct ixgbe_ring*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int ixgbe_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (adapter->xdp_prog) {
		int new_frame_size = new_mtu + ETH_HLEN + ETH_FCS_LEN +
				     VLAN_HLEN;
		int i;

		for (i = 0; i < adapter->num_rx_queues; i++) {
			struct ixgbe_ring *ring = adapter->rx_ring[i];

			if (new_frame_size > ixgbe_rx_bufsz(ring)) {
				e_warn(probe, "Requested MTU size is not supported with XDP\n");
				return -EINVAL;
			}
		}
	}

	/*
	 * For 82599EB we cannot allow legacy VFs to enable their receive
	 * paths when MTU greater than 1500 is configured.  So display a
	 * warning that legacy VFs will be disabled.
	 */
	if ((adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) &&
	    (adapter->hw.mac.type == ixgbe_mac_82599EB) &&
	    (new_mtu > ETH_DATA_LEN))
		e_warn(probe, "Setting MTU > 1500 will disable legacy VFs\n");

	e_info(probe, "changing MTU from %d to %d\n", netdev->mtu, new_mtu);

	/* must set new MTU before calling down or up */
	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		ixgbe_reinit_locked(adapter);

	return 0;
}