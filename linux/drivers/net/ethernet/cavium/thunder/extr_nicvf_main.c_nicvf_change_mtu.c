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
struct nicvf {scalar_t__ xdp_prog; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_XDP_MTU ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ nicvf_update_hw_max_frs (struct nicvf*,int) ; 

__attribute__((used)) static int nicvf_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct nicvf *nic = netdev_priv(netdev);
	int orig_mtu = netdev->mtu;

	/* For now just support only the usual MTU sized frames,
	 * plus some headroom for VLAN, QinQ.
	 */
	if (nic->xdp_prog && new_mtu > MAX_XDP_MTU) {
		netdev_warn(netdev, "Jumbo frames not yet supported with XDP, current MTU %d.\n",
			    netdev->mtu);
		return -EINVAL;
	}

	netdev->mtu = new_mtu;

	if (!netif_running(netdev))
		return 0;

	if (nicvf_update_hw_max_frs(nic, new_mtu)) {
		netdev->mtu = orig_mtu;
		return -EINVAL;
	}

	return 0;
}