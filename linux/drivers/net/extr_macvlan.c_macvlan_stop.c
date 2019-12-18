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
struct net_device {int flags; int /*<<< orphan*/  dismantle; int /*<<< orphan*/  dev_addr; TYPE_1__* netdev_ops; } ;
struct macvlan_dev {int flags; int /*<<< orphan*/  port; int /*<<< orphan*/ * accel_priv; struct net_device* lowerdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_dfwd_del_station ) (struct net_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MACVLAN_FLAG_NOPROMISC ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  macvlan_hash_del (struct macvlan_dev*,int) ; 
 scalar_t__ macvlan_passthru (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macvlan_stop(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	if (vlan->accel_priv) {
		lowerdev->netdev_ops->ndo_dfwd_del_station(lowerdev,
							   vlan->accel_priv);
		vlan->accel_priv = NULL;
	}

	dev_uc_unsync(lowerdev, dev);
	dev_mc_unsync(lowerdev, dev);

	if (macvlan_passthru(vlan->port)) {
		if (!(vlan->flags & MACVLAN_FLAG_NOPROMISC))
			dev_set_promiscuity(lowerdev, -1);
		goto hash_del;
	}

	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);

	if (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(lowerdev, -1);

	dev_uc_del(lowerdev, dev->dev_addr);

hash_del:
	macvlan_hash_del(vlan, !dev->dismantle);
	return 0;
}