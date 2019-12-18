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
struct mlxsw_sp_vr {struct mlxsw_sp_vr* ul_rif; int /*<<< orphan*/  ul_rif_refcnt; int /*<<< orphan*/  rif_count; } ;
struct mlxsw_sp_rif {struct mlxsw_sp_rif* ul_rif; int /*<<< orphan*/  ul_rif_refcnt; int /*<<< orphan*/  rif_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_vr* ERR_CAST (struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_vr* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_vr*) ; 
 int PTR_ERR (struct mlxsw_sp_vr*) ; 
 struct mlxsw_sp_vr* mlxsw_sp_ul_rif_create (struct mlxsw_sp*,struct mlxsw_sp_vr*,struct netlink_ext_ack*) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_put (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mlxsw_sp_rif *
mlxsw_sp_ul_rif_get(struct mlxsw_sp *mlxsw_sp, u32 tb_id,
		    struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_vr *vr;
	int err;

	vr = mlxsw_sp_vr_get(mlxsw_sp, tb_id, extack);
	if (IS_ERR(vr))
		return ERR_CAST(vr);

	if (refcount_inc_not_zero(&vr->ul_rif_refcnt))
		return vr->ul_rif;

	vr->ul_rif = mlxsw_sp_ul_rif_create(mlxsw_sp, vr, extack);
	if (IS_ERR(vr->ul_rif)) {
		err = PTR_ERR(vr->ul_rif);
		goto err_ul_rif_create;
	}

	vr->rif_count++;
	refcount_set(&vr->ul_rif_refcnt, 1);

	return vr->ul_rif;

err_ul_rif_create:
	mlxsw_sp_vr_put(mlxsw_sp, vr);
	return ERR_PTR(err);
}