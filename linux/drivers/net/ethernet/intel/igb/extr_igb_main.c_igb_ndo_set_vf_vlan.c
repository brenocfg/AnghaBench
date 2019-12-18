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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int igb_disable_port_vlan (struct igb_adapter*,int) ; 
 int igb_enable_port_vlan (struct igb_adapter*,int,int,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_ndo_set_vf_vlan(struct net_device *netdev, int vf,
			       u16 vlan, u8 qos, __be16 vlan_proto)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	if ((vf >= adapter->vfs_allocated_count) || (vlan > 4095) || (qos > 7))
		return -EINVAL;

	if (vlan_proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	return (vlan || qos) ? igb_enable_port_vlan(adapter, vf, vlan, qos) :
			       igb_disable_port_vlan(adapter, vf);
}