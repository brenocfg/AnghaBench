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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_vr {int /*<<< orphan*/  rif_count; int /*<<< orphan*/ * mr_table; int /*<<< orphan*/  id; } ;
struct mlxsw_sp_rif_params {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_rif_ops {int (* configure ) (struct mlxsw_sp_rif*) ;int /*<<< orphan*/  (* deconfigure ) (struct mlxsw_sp_rif*) ;int /*<<< orphan*/  (* setup ) (struct mlxsw_sp_rif*,struct mlxsw_sp_rif_params const*) ;struct mlxsw_sp_vr* (* fid_get ) (struct mlxsw_sp_rif*,struct netlink_ext_ack*) ;int /*<<< orphan*/  rif_size; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  dev; struct mlxsw_sp_vr* fid; struct mlxsw_sp_rif_ops const* ops; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_fid {int /*<<< orphan*/  rif_count; int /*<<< orphan*/ * mr_table; int /*<<< orphan*/  id; } ;
struct mlxsw_sp {TYPE_1__* router; struct mlxsw_sp_rif_ops** rif_ops_arr; } ;
typedef  enum mlxsw_sp_rif_type { ____Placeholder_mlxsw_sp_rif_type } mlxsw_sp_rif_type ;
struct TYPE_2__ {struct mlxsw_sp_rif** rifs; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_rif* ERR_CAST (struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_rif* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_vr*) ; 
 int MLXSW_SP_L3_PROTO_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct mlxsw_sp_vr*) ; 
 int /*<<< orphan*/  RT_TABLE_MAIN ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_rif*) ; 
 scalar_t__ l3mdev_fib_table (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_dev_rif_type (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_vr*) ; 
 int mlxsw_sp_mr_rif_add (int /*<<< orphan*/ ,struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_rif_del (int /*<<< orphan*/ ,struct mlxsw_sp_rif*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_counters_alloc (struct mlxsw_sp_rif*) ; 
 int mlxsw_sp_rif_index_alloc (struct mlxsw_sp*,size_t*) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_put (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_vr* stub1 (struct mlxsw_sp_rif*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_rif*,struct mlxsw_sp_rif_params const*) ; 
 int stub3 (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  stub4 (struct mlxsw_sp_rif*) ; 

__attribute__((used)) static struct mlxsw_sp_rif *
mlxsw_sp_rif_create(struct mlxsw_sp *mlxsw_sp,
		    const struct mlxsw_sp_rif_params *params,
		    struct netlink_ext_ack *extack)
{
	u32 tb_id = l3mdev_fib_table(params->dev);
	const struct mlxsw_sp_rif_ops *ops;
	struct mlxsw_sp_fid *fid = NULL;
	enum mlxsw_sp_rif_type type;
	struct mlxsw_sp_rif *rif;
	struct mlxsw_sp_vr *vr;
	u16 rif_index;
	int i, err;

	type = mlxsw_sp_dev_rif_type(mlxsw_sp, params->dev);
	ops = mlxsw_sp->rif_ops_arr[type];

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id ? : RT_TABLE_MAIN, extack);
	if (IS_ERR(vr))
		return ERR_CAST(vr);
	vr->rif_count++;

	err = mlxsw_sp_rif_index_alloc(mlxsw_sp, &rif_index);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported router interfaces");
		goto err_rif_index_alloc;
	}

	rif = mlxsw_sp_rif_alloc(ops->rif_size, rif_index, vr->id, params->dev);
	if (!rif) {
		err = -ENOMEM;
		goto err_rif_alloc;
	}
	dev_hold(rif->dev);
	mlxsw_sp->router->rifs[rif_index] = rif;
	rif->mlxsw_sp = mlxsw_sp;
	rif->ops = ops;

	if (ops->fid_get) {
		fid = ops->fid_get(rif, extack);
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			goto err_fid_get;
		}
		rif->fid = fid;
	}

	if (ops->setup)
		ops->setup(rif, params);

	err = ops->configure(rif);
	if (err)
		goto err_configure;

	for (i = 0; i < MLXSW_SP_L3_PROTO_MAX; i++) {
		err = mlxsw_sp_mr_rif_add(vr->mr_table[i], rif);
		if (err)
			goto err_mr_rif_add;
	}

	mlxsw_sp_rif_counters_alloc(rif);

	return rif;

err_mr_rif_add:
	for (i--; i >= 0; i--)
		mlxsw_sp_mr_rif_del(vr->mr_table[i], rif);
	ops->deconfigure(rif);
err_configure:
	if (fid)
		mlxsw_sp_fid_put(fid);
err_fid_get:
	mlxsw_sp->router->rifs[rif_index] = NULL;
	dev_put(rif->dev);
	kfree(rif);
err_rif_alloc:
err_rif_index_alloc:
	vr->rif_count--;
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	return ERR_PTR(err);
}