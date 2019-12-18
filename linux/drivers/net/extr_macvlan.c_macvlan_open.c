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
struct net_device {int features; int flags; int /*<<< orphan*/  dev_addr; TYPE_1__* netdev_ops; } ;
struct macvlan_dev {int flags; int /*<<< orphan*/ * accel_priv; int /*<<< orphan*/  port; struct net_device* lowerdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_dfwd_del_station ) (struct net_device*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* ndo_dfwd_add_station ) (struct net_device*,struct net_device*) ;} ;

/* Variables and functions */
 int EADDRINUSE ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int MACVLAN_FLAG_NOPROMISC ; 
 int NETIF_F_HW_L2FW_DOFFLOAD ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ macvlan_addr_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_hash_add (struct macvlan_dev*) ; 
 scalar_t__ macvlan_passthru (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * stub1 (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macvlan_open(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;
	int err;

	if (macvlan_passthru(vlan->port)) {
		if (!(vlan->flags & MACVLAN_FLAG_NOPROMISC)) {
			err = dev_set_promiscuity(lowerdev, 1);
			if (err < 0)
				goto out;
		}
		goto hash_add;
	}

	err = -EADDRINUSE;
	if (macvlan_addr_busy(vlan->port, dev->dev_addr))
		goto out;

	/* Attempt to populate accel_priv which is used to offload the L2
	 * forwarding requests for unicast packets.
	 */
	if (lowerdev->features & NETIF_F_HW_L2FW_DOFFLOAD)
		vlan->accel_priv =
		      lowerdev->netdev_ops->ndo_dfwd_add_station(lowerdev, dev);

	/* If earlier attempt to offload failed, or accel_priv is not
	 * populated we must add the unicast address to the lower device.
	 */
	if (IS_ERR_OR_NULL(vlan->accel_priv)) {
		vlan->accel_priv = NULL;
		err = dev_uc_add(lowerdev, dev->dev_addr);
		if (err < 0)
			goto out;
	}

	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(lowerdev, 1);
		if (err < 0)
			goto del_unicast;
	}

	if (dev->flags & IFF_PROMISC) {
		err = dev_set_promiscuity(lowerdev, 1);
		if (err < 0)
			goto clear_multi;
	}

hash_add:
	macvlan_hash_add(vlan);
	return 0;

clear_multi:
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);
del_unicast:
	if (vlan->accel_priv) {
		lowerdev->netdev_ops->ndo_dfwd_del_station(lowerdev,
							   vlan->accel_priv);
		vlan->accel_priv = NULL;
	} else {
		dev_uc_del(lowerdev, dev->dev_addr);
	}
out:
	return err;
}