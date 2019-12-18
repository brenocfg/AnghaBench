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
typedef  scalar_t__ u32 ;
struct mlxsw_sp_acl_atcam_region_12kb {scalar_t__ max_lkey_id; int /*<<< orphan*/  used_lkey_id; int /*<<< orphan*/  lkey_ht; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_atcam_region_12kb* priv; } ;
struct mlxsw_sp_acl_atcam_lkey_id_ht_key {int dummy; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  ht_node; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ht_key; scalar_t__ id; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 struct mlxsw_sp_acl_atcam_lkey_id* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_atcam_lkey_id*) ; 
 struct mlxsw_sp_acl_atcam_lkey_id* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlxsw_sp_acl_atcam_lkey_id_ht_key*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_lkey_id_ht_params ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_lkey_id_create(struct mlxsw_sp_acl_atcam_region *aregion,
				  struct mlxsw_sp_acl_atcam_lkey_id_ht_key *ht_key)
{
	struct mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	struct mlxsw_sp_acl_atcam_lkey_id *lkey_id;
	u32 id;
	int err;

	id = find_first_zero_bit(region_12kb->used_lkey_id,
				 region_12kb->max_lkey_id);
	if (id < region_12kb->max_lkey_id)
		__set_bit(id, region_12kb->used_lkey_id);
	else
		return ERR_PTR(-ENOBUFS);

	lkey_id = kzalloc(sizeof(*lkey_id), GFP_KERNEL);
	if (!lkey_id) {
		err = -ENOMEM;
		goto err_lkey_id_alloc;
	}

	lkey_id->id = id;
	memcpy(&lkey_id->ht_key, ht_key, sizeof(*ht_key));
	refcount_set(&lkey_id->refcnt, 1);

	err = rhashtable_insert_fast(&region_12kb->lkey_ht,
				     &lkey_id->ht_node,
				     mlxsw_sp_acl_atcam_lkey_id_ht_params);
	if (err)
		goto err_rhashtable_insert;

	return lkey_id;

err_rhashtable_insert:
	kfree(lkey_id);
err_lkey_id_alloc:
	__clear_bit(id, region_12kb->used_lkey_id);
	return ERR_PTR(err);
}