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
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_vfs; TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int trusted; int clear_to_send; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  ixgbe_ping_vf (struct ixgbe_adapter*,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

int ixgbe_ndo_set_vf_trust(struct net_device *netdev, int vf, bool setting)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	/* nothing to do */
	if (adapter->vfinfo[vf].trusted == setting)
		return 0;

	adapter->vfinfo[vf].trusted = setting;

	/* reset VF to reconfigure features */
	adapter->vfinfo[vf].clear_to_send = false;
	ixgbe_ping_vf(adapter, vf);

	e_info(drv, "VF %u is %strusted\n", vf, setting ? "" : "not ");

	return 0;
}