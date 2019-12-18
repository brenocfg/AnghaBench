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
struct mlxsw_sp_acl_erp_table {int dummy; } ;
struct mlxsw_sp_acl_erp_key {scalar_t__ mask; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  key; struct mlxsw_sp_acl_erp_table* erp_table; int /*<<< orphan*/  mask_bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_erp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_TCAM_MASK_LEN ; 
 int /*<<< orphan*/  bitmap_from_arr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 struct mlxsw_sp_acl_erp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlxsw_sp_acl_erp_key*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ctcam_dec (struct mlxsw_sp_acl_erp_table*) ; 
 int mlxsw_sp_acl_erp_ctcam_inc (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_erp_master_mask_set (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_erp_region_ctcam_enable (struct mlxsw_sp_acl_erp_table*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_ctcam_mask_create(struct mlxsw_sp_acl_erp_table *erp_table,
				   struct mlxsw_sp_acl_erp_key *key)
{
	struct mlxsw_sp_acl_erp *erp;
	int err;

	erp = kzalloc(sizeof(*erp), GFP_KERNEL);
	if (!erp)
		return ERR_PTR(-ENOMEM);

	memcpy(&erp->key, key, sizeof(*key));
	bitmap_from_arr32(erp->mask_bitmap, (u32 *) key->mask,
			  MLXSW_SP_ACL_TCAM_MASK_LEN);

	err = mlxsw_sp_acl_erp_ctcam_inc(erp_table);
	if (err)
		goto err_erp_ctcam_inc;

	erp->erp_table = erp_table;

	err = mlxsw_sp_acl_erp_master_mask_set(erp_table, &erp->key);
	if (err)
		goto err_master_mask_set;

	err = mlxsw_sp_acl_erp_region_ctcam_enable(erp_table);
	if (err)
		goto err_erp_region_ctcam_enable;

	return erp;

err_erp_region_ctcam_enable:
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
err_master_mask_set:
	mlxsw_sp_acl_erp_ctcam_dec(erp_table);
err_erp_ctcam_inc:
	kfree(erp);
	return ERR_PTR(err);
}