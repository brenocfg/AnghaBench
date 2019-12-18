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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  fid; int /*<<< orphan*/  rif_index; } ;
struct mlxsw_sp {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  lowerdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_fdb_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_vrrp_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct macvlan_dev* netdev_priv (struct net_device const*) ; 

void mlxsw_sp_rif_macvlan_del(struct mlxsw_sp *mlxsw_sp,
			      const struct net_device *macvlan_dev)
{
	struct macvlan_dev *vlan = netdev_priv(macvlan_dev);
	struct mlxsw_sp_rif *rif;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, vlan->lowerdev);
	/* If we do not have a RIF, then we already took care of
	 * removing the macvlan's MAC during RIF deletion.
	 */
	if (!rif)
		return;
	mlxsw_sp_rif_vrrp_op(mlxsw_sp, rif->rif_index, macvlan_dev->dev_addr,
			     false);
	mlxsw_sp_rif_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
			    mlxsw_sp_fid_index(rif->fid), false);
}