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
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; int flags; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int EBUSY ; 
 scalar_t__ mlxsw_sp_fid_8021q_vid (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp_fid* mlxsw_sp_rif_fid (struct mlxsw_sp_rif*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device const*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device const*,char*) ; 

__attribute__((used)) static int
mlxsw_sp_br_ban_rif_pvid_change(struct mlxsw_sp *mlxsw_sp,
				const struct net_device *br_dev,
				const struct switchdev_obj_port_vlan *vlan)
{
	struct mlxsw_sp_rif *rif;
	struct mlxsw_sp_fid *fid;
	u16 pvid;
	u16 vid;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, br_dev);
	if (!rif)
		return 0;
	fid = mlxsw_sp_rif_fid(rif);
	pvid = mlxsw_sp_fid_8021q_vid(fid);

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; ++vid) {
		if (vlan->flags & BRIDGE_VLAN_INFO_PVID) {
			if (vid != pvid) {
				netdev_err(br_dev, "Can't change PVID, it's used by router interface\n");
				return -EBUSY;
			}
		} else {
			if (vid == pvid) {
				netdev_err(br_dev, "Can't remove PVID, it's used by router interface\n");
				return -EBUSY;
			}
		}
	}

	return 0;
}