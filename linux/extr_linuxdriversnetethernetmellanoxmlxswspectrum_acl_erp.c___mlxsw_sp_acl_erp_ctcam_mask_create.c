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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  num_ctcam_erps; int /*<<< orphan*/  erp_ht; int /*<<< orphan*/ * ops; } ;
struct mlxsw_sp_acl_erp_key {scalar_t__ mask; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  ht_node; struct mlxsw_sp_acl_erp_table* erp_table; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  mask_bitmap; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_erp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_TCAM_MASK_LEN ; 
 int /*<<< orphan*/  bitmap_from_arr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erp_multiple_masks_ops ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 struct mlxsw_sp_acl_erp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlxsw_sp_acl_erp_key*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_master_mask_set (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_region_ctcam_enable (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_erp *
__mlxsw_sp_acl_erp_ctcam_mask_create(struct mlxsw_sp_acl_erp_table *erp_table,
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
	refcount_set(&erp->refcnt, 1);
	erp_table->num_ctcam_erps++;
	erp->erp_table = erp_table;

	err = mlxsw_sp_acl_erp_master_mask_set(erp_table, erp);
	if (err)
		goto err_master_mask_set;

	err = rhashtable_insert_fast(&erp_table->erp_ht, &erp->ht_node,
				     mlxsw_sp_acl_erp_ht_params);
	if (err)
		goto err_rhashtable_insert;

	err = mlxsw_sp_acl_erp_region_ctcam_enable(erp_table);
	if (err)
		goto err_erp_region_ctcam_enable;

	/* When C-TCAM is used, the eRP table must be used */
	erp_table->ops = &erp_multiple_masks_ops;

	return erp;

err_erp_region_ctcam_enable:
	rhashtable_remove_fast(&erp_table->erp_ht, &erp->ht_node,
			       mlxsw_sp_acl_erp_ht_params);
err_rhashtable_insert:
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, erp);
err_master_mask_set:
	erp_table->num_ctcam_erps--;
	kfree(erp);
	return ERR_PTR(err);
}