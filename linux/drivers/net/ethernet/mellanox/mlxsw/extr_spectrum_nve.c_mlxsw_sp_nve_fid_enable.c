#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_nve_params {size_t type; int /*<<< orphan*/  vni; TYPE_1__* dev; } ;
struct mlxsw_sp_nve_ops {int (* fdb_replay ) (TYPE_1__*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ;int /*<<< orphan*/  (* nve_config ) (struct mlxsw_sp_nve*,TYPE_1__*,struct mlxsw_sp_nve_config*) ;int /*<<< orphan*/  (* can_offload ) (struct mlxsw_sp_nve*,TYPE_1__*,struct netlink_ext_ack*) ;} ;
struct mlxsw_sp_nve_config {int dummy; } ;
struct mlxsw_sp_nve {struct mlxsw_sp_nve_config config; scalar_t__ num_nve_tunnels; struct mlxsw_sp_nve_ops** nve_ops_arr; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ memcmp (struct mlxsw_sp_nve_config*,struct mlxsw_sp_nve_config*,int) ; 
 int /*<<< orphan*/  memset (struct mlxsw_sp_nve_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_vni_clear (struct mlxsw_sp_fid*) ; 
 int mlxsw_sp_fid_vni_set (struct mlxsw_sp_fid*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_tunnel_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_nve_tunnel_init (struct mlxsw_sp*,struct mlxsw_sp_nve_config*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_nve*,TYPE_1__*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_nve*,TYPE_1__*,struct mlxsw_sp_nve_config*) ; 
 int stub3 (TYPE_1__*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

int mlxsw_sp_nve_fid_enable(struct mlxsw_sp *mlxsw_sp, struct mlxsw_sp_fid *fid,
			    struct mlxsw_sp_nve_params *params,
			    struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;
	const struct mlxsw_sp_nve_ops *ops;
	struct mlxsw_sp_nve_config config;
	int err;

	ops = nve->nve_ops_arr[params->type];

	if (!ops->can_offload(nve, params->dev, extack))
		return -EINVAL;

	memset(&config, 0, sizeof(config));
	ops->nve_config(nve, params->dev, &config);
	if (nve->num_nve_tunnels &&
	    memcmp(&config, &nve->config, sizeof(config))) {
		NL_SET_ERR_MSG_MOD(extack, "Conflicting NVE tunnels configuration");
		return -EINVAL;
	}

	err = mlxsw_sp_nve_tunnel_init(mlxsw_sp, &config);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack, "Failed to initialize NVE tunnel");
		return err;
	}

	err = mlxsw_sp_fid_vni_set(fid, params->type, params->vni,
				   params->dev->ifindex);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack, "Failed to set VNI on FID");
		goto err_fid_vni_set;
	}

	nve->config = config;

	err = ops->fdb_replay(params->dev, params->vni, extack);
	if (err)
		goto err_fdb_replay;

	return 0;

err_fdb_replay:
	mlxsw_sp_fid_vni_clear(fid);
err_fid_vni_set:
	mlxsw_sp_nve_tunnel_fini(mlxsw_sp);
	return err;
}