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
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_vr {int /*<<< orphan*/  tb_id; struct mlxsw_sp_mr_table** mr_table; struct mlxsw_sp_mr_table* fib6; struct mlxsw_sp_mr_table* fib4; int /*<<< orphan*/  id; } ;
struct mlxsw_sp_mr_table {int dummy; } ;
typedef  struct mlxsw_sp_mr_table mlxsw_sp_fib ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct mlxsw_sp_vr* ERR_CAST (struct mlxsw_sp_mr_table*) ; 
 struct mlxsw_sp_vr* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_mr_table*) ; 
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct mlxsw_sp_mr_table*) ; 
 struct mlxsw_sp_mr_table* mlxsw_sp_fib_create (struct mlxsw_sp*,struct mlxsw_sp_vr*,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_destroy (struct mlxsw_sp*,struct mlxsw_sp_mr_table*) ; 
 struct mlxsw_sp_mr_table* mlxsw_sp_mr_table_create (struct mlxsw_sp*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_table_destroy (struct mlxsw_sp_mr_table*) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_find_unused (struct mlxsw_sp*) ; 

__attribute__((used)) static struct mlxsw_sp_vr *mlxsw_sp_vr_create(struct mlxsw_sp *mlxsw_sp,
					      u32 tb_id,
					      struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_mr_table *mr4_table, *mr6_table;
	struct mlxsw_sp_fib *fib4;
	struct mlxsw_sp_fib *fib6;
	struct mlxsw_sp_vr *vr;
	int err;

	vr = mlxsw_sp_vr_find_unused(mlxsw_sp);
	if (!vr) {
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported virtual routers");
		return ERR_PTR(-EBUSY);
	}
	fib4 = mlxsw_sp_fib_create(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV4);
	if (IS_ERR(fib4))
		return ERR_CAST(fib4);
	fib6 = mlxsw_sp_fib_create(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV6);
	if (IS_ERR(fib6)) {
		err = PTR_ERR(fib6);
		goto err_fib6_create;
	}
	mr4_table = mlxsw_sp_mr_table_create(mlxsw_sp, vr->id,
					     MLXSW_SP_L3_PROTO_IPV4);
	if (IS_ERR(mr4_table)) {
		err = PTR_ERR(mr4_table);
		goto err_mr4_table_create;
	}
	mr6_table = mlxsw_sp_mr_table_create(mlxsw_sp, vr->id,
					     MLXSW_SP_L3_PROTO_IPV6);
	if (IS_ERR(mr6_table)) {
		err = PTR_ERR(mr6_table);
		goto err_mr6_table_create;
	}

	vr->fib4 = fib4;
	vr->fib6 = fib6;
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV4] = mr4_table;
	vr->mr_table[MLXSW_SP_L3_PROTO_IPV6] = mr6_table;
	vr->tb_id = tb_id;
	return vr;

err_mr6_table_create:
	mlxsw_sp_mr_table_destroy(mr4_table);
err_mr4_table_create:
	mlxsw_sp_fib_destroy(mlxsw_sp, fib6);
err_fib6_create:
	mlxsw_sp_fib_destroy(mlxsw_sp, fib4);
	return ERR_PTR(err);
}