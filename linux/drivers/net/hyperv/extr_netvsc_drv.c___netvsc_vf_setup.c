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
struct net_device {int mtu; int flags; } ;

/* Variables and functions */
 int IFF_SLAVE ; 
 int /*<<< orphan*/  dev_change_flags (struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_mc_sync (struct net_device*,struct net_device*) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int dev_set_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_sync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static void __netvsc_vf_setup(struct net_device *ndev,
			      struct net_device *vf_netdev)
{
	int ret;

	/* Align MTU of VF with master */
	ret = dev_set_mtu(vf_netdev, ndev->mtu);
	if (ret)
		netdev_warn(vf_netdev,
			    "unable to change mtu to %u\n", ndev->mtu);

	/* set multicast etc flags on VF */
	dev_change_flags(vf_netdev, ndev->flags | IFF_SLAVE, NULL);

	/* sync address list from ndev to VF */
	netif_addr_lock_bh(ndev);
	dev_uc_sync(vf_netdev, ndev);
	dev_mc_sync(vf_netdev, ndev);
	netif_addr_unlock_bh(ndev);

	if (netif_running(ndev)) {
		ret = dev_open(vf_netdev, NULL);
		if (ret)
			netdev_warn(vf_netdev,
				    "unable to open: %d\n", ret);
	}
}