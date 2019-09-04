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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  fid; TYPE_1__* ops; int /*<<< orphan*/  rif_index; } ;
struct mlxsw_sp {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  lowerdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fdb_del ) (struct mlxsw_sp_rif*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_rif_fdb_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_rif_vrrp_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct macvlan_dev* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_rif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_rif_macvlan_add(struct mlxsw_sp *mlxsw_sp,
				    const struct net_device *macvlan_dev,
				    struct netlink_ext_ack *extack)
{
	struct macvlan_dev *vlan = netdev_priv(macvlan_dev);
	struct mlxsw_sp_rif *rif;
	int err;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, vlan->lowerdev);
	if (!rif) {
		NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
		return -EOPNOTSUPP;
	}

	err = mlxsw_sp_rif_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
				  mlxsw_sp_fid_index(rif->fid), true);
	if (err)
		return err;

	err = mlxsw_sp_rif_vrrp_op(mlxsw_sp, rif->rif_index,
				   macvlan_dev->dev_addr, true);
	if (err)
		goto err_rif_vrrp_add;

	/* Make sure the bridge driver does not have this MAC pointing at
	 * some other port.
	 */
	if (rif->ops->fdb_del)
		rif->ops->fdb_del(rif, macvlan_dev->dev_addr);

	return 0;

err_rif_vrrp_add:
	mlxsw_sp_rif_fdb_op(mlxsw_sp, macvlan_dev->dev_addr,
			    mlxsw_sp_fid_index(rif->fid), false);
	return err;
}