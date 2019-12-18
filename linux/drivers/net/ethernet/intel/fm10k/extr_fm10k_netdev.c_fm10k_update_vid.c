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
typedef  int u16 ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
struct fm10k_ring {int vid; } ;
struct fm10k_l2_accel {int size; int dglort; struct net_device** macvlan; } ;
struct TYPE_2__ {int default_vid; int /*<<< orphan*/  addr; scalar_t__ vlan_override; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {int num_rx_queues; int glort; int vid; int /*<<< orphan*/  state; int /*<<< orphan*/  active_vlans; struct fm10k_ring** rx_ring; struct fm10k_hw hw; struct fm10k_l2_accel* l2_accel; } ;
typedef  int s32 ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int FM10K_VLAN_CLEAR ; 
 int IFF_PROMISC ; 
 int VLAN_N_VID ; 
 int __FM10K_DOWN ; 
 int /*<<< orphan*/  __dev_mc_unsync (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_unsync (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mc_vlan_unsync ; 
 int fm10k_queue_mac_request (struct fm10k_intfc*,int,int /*<<< orphan*/ ,int,int) ; 
 int fm10k_queue_vlan_request (struct fm10k_intfc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_uc_vlan_unsync ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm10k_update_vid(struct net_device *netdev, u16 vid, bool set)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_l2_accel *l2_accel = interface->l2_accel;
	struct fm10k_hw *hw = &interface->hw;
	u16 glort;
	s32 err;
	int i;

	/* updates do not apply to VLAN 0 */
	if (!vid)
		return 0;

	if (vid >= VLAN_N_VID)
		return -EINVAL;

	/* Verify that we have permission to add VLANs. If this is a request
	 * to remove a VLAN, we still want to allow the user to remove the
	 * VLAN device. In that case, we need to clear the bit in the
	 * active_vlans bitmask.
	 */
	if (set && hw->mac.vlan_override)
		return -EACCES;

	/* update active_vlans bitmask */
	set_bit(vid, interface->active_vlans);
	if (!set)
		clear_bit(vid, interface->active_vlans);

	/* disable the default VLAN ID on ring if we have an active VLAN */
	for (i = 0; i < interface->num_rx_queues; i++) {
		struct fm10k_ring *rx_ring = interface->rx_ring[i];
		u16 rx_vid = rx_ring->vid & (VLAN_N_VID - 1);

		if (test_bit(rx_vid, interface->active_vlans))
			rx_ring->vid |= FM10K_VLAN_CLEAR;
		else
			rx_ring->vid &= ~FM10K_VLAN_CLEAR;
	}

	/* If our VLAN has been overridden, there is no reason to send VLAN
	 * removal requests as they will be silently ignored.
	 */
	if (hw->mac.vlan_override)
		return 0;

	/* Do not remove default VLAN ID related entries from VLAN and MAC
	 * tables
	 */
	if (!set && vid == hw->mac.default_vid)
		return 0;

	/* Do not throw an error if the interface is down. We will sync once
	 * we come up
	 */
	if (test_bit(__FM10K_DOWN, interface->state))
		return 0;

	fm10k_mbx_lock(interface);

	/* only need to update the VLAN if not in promiscuous mode */
	if (!(netdev->flags & IFF_PROMISC)) {
		err = fm10k_queue_vlan_request(interface, vid, 0, set);
		if (err)
			goto err_out;
	}

	/* Update our base MAC address */
	err = fm10k_queue_mac_request(interface, interface->glort,
				      hw->mac.addr, vid, set);
	if (err)
		goto err_out;

	/* Update L2 accelerated macvlan addresses */
	if (l2_accel) {
		for (i = 0; i < l2_accel->size; i++) {
			struct net_device *sdev = l2_accel->macvlan[i];

			if (!sdev)
				continue;

			glort = l2_accel->dglort + 1 + i;

			fm10k_queue_mac_request(interface, glort,
						sdev->dev_addr,
						vid, set);
		}
	}

	/* set VLAN ID prior to syncing/unsyncing the VLAN */
	interface->vid = vid + (set ? VLAN_N_VID : 0);

	/* Update the unicast and multicast address list to add/drop VLAN */
	__dev_uc_unsync(netdev, fm10k_uc_vlan_unsync);
	__dev_mc_unsync(netdev, fm10k_mc_vlan_unsync);

err_out:
	fm10k_mbx_unlock(interface);

	return err;
}