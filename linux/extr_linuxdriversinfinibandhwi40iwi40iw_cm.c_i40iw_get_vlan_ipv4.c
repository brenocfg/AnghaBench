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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_NO_VLAN ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static u16 i40iw_get_vlan_ipv4(u32 *addr)
{
	struct net_device *netdev;
	u16 vlan_id = I40IW_NO_VLAN;

	netdev = ip_dev_find(&init_net, htonl(addr[0]));
	if (netdev) {
		vlan_id = rdma_vlan_dev_vlan_id(netdev);
		dev_put(netdev);
	}
	return vlan_id;
}