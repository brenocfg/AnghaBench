#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_1__* dev; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct mlxsw_sp_fid* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_fid*) ; 
 int mlxsw_sp_bridge_8021d_vxlan_join (struct mlxsw_sp_bridge_device*,struct net_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_device* mlxsw_sp_bridge_vxlan_dev_find (TYPE_1__*) ; 
 struct mlxsw_sp_fid* mlxsw_sp_fid_8021d_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_fid*) ; 
 scalar_t__ mlxsw_sp_fid_vni_is_set (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_bridge_8021d_fid_get(struct mlxsw_sp_bridge_device *bridge_device,
			      u16 vid, struct netlink_ext_ack *extack)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);
	struct net_device *vxlan_dev;
	struct mlxsw_sp_fid *fid;
	int err;

	fid = mlxsw_sp_fid_8021d_get(mlxsw_sp, bridge_device->dev->ifindex);
	if (IS_ERR(fid))
		return fid;

	if (mlxsw_sp_fid_vni_is_set(fid))
		return fid;

	vxlan_dev = mlxsw_sp_bridge_vxlan_dev_find(bridge_device->dev);
	if (!vxlan_dev)
		return fid;

	if (!netif_running(vxlan_dev))
		return fid;

	err = mlxsw_sp_bridge_8021d_vxlan_join(bridge_device, vxlan_dev, 0,
					       extack);
	if (err)
		goto err_vxlan_join;

	return fid;

err_vxlan_join:
	mlxsw_sp_fid_put(fid);
	return ERR_PTR(err);
}