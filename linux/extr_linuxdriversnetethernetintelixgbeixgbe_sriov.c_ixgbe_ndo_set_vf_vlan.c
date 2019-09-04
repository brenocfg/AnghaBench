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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_vfs; TYPE_1__* vfinfo; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {scalar_t__ pf_vlan; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ixgbe_disable_port_vlan (struct ixgbe_adapter*,int) ; 
 int ixgbe_enable_port_vlan (struct ixgbe_adapter*,int,int,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

int ixgbe_ndo_set_vf_vlan(struct net_device *netdev, int vf, u16 vlan,
			  u8 qos, __be16 vlan_proto)
{
	int err = 0;
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if ((vf >= adapter->num_vfs) || (vlan > 4095) || (qos > 7))
		return -EINVAL;
	if (vlan_proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;
	if (vlan || qos) {
		/* Check if there is already a port VLAN set, if so
		 * we have to delete the old one first before we
		 * can set the new one.  The usage model had
		 * previously assumed the user would delete the
		 * old port VLAN before setting a new one but this
		 * is not necessarily the case.
		 */
		if (adapter->vfinfo[vf].pf_vlan)
			err = ixgbe_disable_port_vlan(adapter, vf);
		if (err)
			goto out;
		err = ixgbe_enable_port_vlan(adapter, vf, vlan, qos);
	} else {
		err = ixgbe_disable_port_vlan(adapter, vf);
	}

out:
	return err;
}