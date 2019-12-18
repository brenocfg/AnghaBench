#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  added_by_user; } ;
struct mlxsw_sp_switchdev_event_work {scalar_t__ event; TYPE_2__ fdb_info; struct net_device* dev; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_1__* ops; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {struct mlxsw_sp_fid* (* fid_lookup ) (struct mlxsw_sp_bridge_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ SWITCHDEV_FDB_ADD_TO_DEVICE ; 
 scalar_t__ SWITCHDEV_FDB_DEL_TO_DEVICE ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_fid*) ; 
 int mlxsw_sp_fid_vni (struct mlxsw_sp_fid*,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_bridge_vxlan_fdb_event (struct mlxsw_sp*,struct mlxsw_sp_switchdev_event_work*,struct mlxsw_sp_fid*,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bridge_master (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 struct mlxsw_sp_fid* stub1 (struct mlxsw_sp_bridge_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_switchdev_bridge_nve_fdb_event(struct mlxsw_sp_switchdev_event_work *
					switchdev_work)
{
	struct mlxsw_sp_bridge_device *bridge_device;
	struct net_device *dev = switchdev_work->dev;
	struct net_device *br_dev;
	struct mlxsw_sp *mlxsw_sp;
	struct mlxsw_sp_fid *fid;
	__be32 vni;
	int err;

	if (switchdev_work->event != SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    switchdev_work->event != SWITCHDEV_FDB_DEL_TO_DEVICE)
		return;

	if (switchdev_work->event == SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    !switchdev_work->fdb_info.added_by_user)
		return;

	if (!netif_running(dev))
		return;
	br_dev = netdev_master_upper_dev_get(dev);
	if (!br_dev)
		return;
	if (!netif_is_bridge_master(br_dev))
		return;
	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	if (!mlxsw_sp)
		return;
	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	if (!bridge_device)
		return;

	fid = bridge_device->ops->fid_lookup(bridge_device,
					     switchdev_work->fdb_info.vid);
	if (!fid)
		return;

	err = mlxsw_sp_fid_vni(fid, &vni);
	if (err)
		goto out;

	mlxsw_sp_switchdev_bridge_vxlan_fdb_event(mlxsw_sp, switchdev_work, fid,
						  vni);

out:
	mlxsw_sp_fid_put(fid);
}