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
typedef  int /*<<< orphan*/  u8 ;
struct objagg_obj {int dummy; } ;
struct mlxsw_sp_acl_erp_mask {int dummy; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_erp* objagg_obj_root_priv (struct objagg_obj*) ; 

u8 mlxsw_sp_acl_erp_mask_erp_id(const struct mlxsw_sp_acl_erp_mask *erp_mask)
{
	struct objagg_obj *objagg_obj = (struct objagg_obj *) erp_mask;
	const struct mlxsw_sp_acl_erp *erp = objagg_obj_root_priv(objagg_obj);

	return erp->id;
}