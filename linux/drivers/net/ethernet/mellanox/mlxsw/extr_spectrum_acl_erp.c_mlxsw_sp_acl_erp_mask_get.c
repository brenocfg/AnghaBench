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
struct objagg_obj {int dummy; } ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  objagg_lock; int /*<<< orphan*/  objagg; } ;
struct mlxsw_sp_acl_erp_mask {int dummy; } ;
struct mlxsw_sp_acl_erp_key {int ctcam; int /*<<< orphan*/  mask; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_erp_mask* ERR_CAST (struct objagg_obj*) ; 
 scalar_t__ IS_ERR (struct objagg_obj*) ; 
 int /*<<< orphan*/  MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct objagg_obj* objagg_obj_get (int /*<<< orphan*/ ,struct mlxsw_sp_acl_erp_key*) ; 

struct mlxsw_sp_acl_erp_mask *
mlxsw_sp_acl_erp_mask_get(struct mlxsw_sp_acl_atcam_region *aregion,
			  const char *mask, bool ctcam)
{
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	struct mlxsw_sp_acl_erp_key key;
	struct objagg_obj *objagg_obj;

	memcpy(key.mask, mask, MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);
	key.ctcam = ctcam;
	mutex_lock(&erp_table->objagg_lock);
	objagg_obj = objagg_obj_get(erp_table->objagg, &key);
	mutex_unlock(&erp_table->objagg_lock);
	if (IS_ERR(objagg_obj))
		return ERR_CAST(objagg_obj);
	return (struct mlxsw_sp_acl_erp_mask *) objagg_obj;
}