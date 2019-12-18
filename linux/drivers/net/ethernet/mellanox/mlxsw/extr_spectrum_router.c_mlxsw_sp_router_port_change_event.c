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
struct net_device {scalar_t__ mtu; int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_vr {int /*<<< orphan*/ * mr_table; } ;
struct mlxsw_sp_rif {scalar_t__ mtu; size_t vr_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  rif_index; int /*<<< orphan*/  fid; struct net_device* dev; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {struct mlxsw_sp_vr* vrs; } ;

/* Variables and functions */
 int MLXSW_SP_L3_PROTO_MAX ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_rif_mtu_update (int /*<<< orphan*/ ,struct mlxsw_sp_rif*,scalar_t__) ; 
 int mlxsw_sp_rif_edit (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int mlxsw_sp_rif_fdb_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_router_port_change_event(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_rif *rif)
{
	struct net_device *dev = rif->dev;
	u16 fid_index;
	int err;

	fid_index = mlxsw_sp_fid_index(rif->fid);

	err = mlxsw_sp_rif_fdb_op(mlxsw_sp, rif->addr, fid_index, false);
	if (err)
		return err;

	err = mlxsw_sp_rif_edit(mlxsw_sp, rif->rif_index, dev->dev_addr,
				dev->mtu);
	if (err)
		goto err_rif_edit;

	err = mlxsw_sp_rif_fdb_op(mlxsw_sp, dev->dev_addr, fid_index, true);
	if (err)
		goto err_rif_fdb_op;

	if (rif->mtu != dev->mtu) {
		struct mlxsw_sp_vr *vr;
		int i;

		/* The RIF is relevant only to its mr_table instance, as unlike
		 * unicast routing, in multicast routing a RIF cannot be shared
		 * between several multicast routing tables.
		 */
		vr = &mlxsw_sp->router->vrs[rif->vr_id];
		for (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++)
			mlxsw_sp_mr_rif_mtu_update(vr->mr_table[i],
						   rif, dev->mtu);
	}

	ether_addr_copy(rif->addr, dev->dev_addr);
	rif->mtu = dev->mtu;

	netdev_dbg(dev, "Updated RIF=%d\n", rif->rif_index);

	return 0;

err_rif_fdb_op:
	mlxsw_sp_rif_edit(mlxsw_sp, rif->rif_index, rif->addr, rif->mtu);
err_rif_edit:
	mlxsw_sp_rif_fdb_op(mlxsw_sp, rif->addr, fid_index, true);
	return err;
}