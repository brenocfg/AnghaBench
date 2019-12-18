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
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_1__* ops; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;
struct TYPE_2__ {struct mlxsw_sp_fid* (* fid_get ) (struct mlxsw_sp_bridge_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlxsw_sp_fid* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device const*) ; 
 struct mlxsw_sp_fid* stub1 (struct mlxsw_sp_bridge_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

struct mlxsw_sp_fid *mlxsw_sp_bridge_fid_get(struct mlxsw_sp *mlxsw_sp,
					     const struct net_device *br_dev,
					     u16 vid,
					     struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_bridge_device *bridge_device;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	if (WARN_ON(!bridge_device))
		return ERR_PTR(-EINVAL);

	return bridge_device->ops->fid_get(bridge_device, vid, extack);
}