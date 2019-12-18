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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_notifier ; 
 int /*<<< orphan*/  netif_is_vxlan (struct net_device const*) ; 
 int vxlan_fdb_replay (struct net_device const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
mlxsw_sp_nve_vxlan_fdb_replay(const struct net_device *nve_dev, __be32 vni,
			      struct netlink_ext_ack *extack)
{
	if (WARN_ON(!netif_is_vxlan(nve_dev)))
		return -EINVAL;
	return vxlan_fdb_replay(nve_dev, vni, &mlxsw_sp_switchdev_notifier,
				extack);
}