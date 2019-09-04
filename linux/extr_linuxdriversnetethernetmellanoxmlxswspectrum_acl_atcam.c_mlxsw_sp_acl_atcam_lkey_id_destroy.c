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
struct mlxsw_sp_acl_atcam_region_12kb {int /*<<< orphan*/  used_lkey_id; int /*<<< orphan*/  lkey_ht; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_atcam_region_12kb* priv; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  ht_node; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_atcam_lkey_id*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_lkey_id_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_atcam_lkey_id_destroy(struct mlxsw_sp_acl_atcam_region *aregion,
				   struct mlxsw_sp_acl_atcam_lkey_id *lkey_id)
{
	struct mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	u32 id = lkey_id->id;

	rhashtable_remove_fast(&region_12kb->lkey_ht, &lkey_id->ht_node,
			       mlxsw_sp_acl_atcam_lkey_id_ht_params);
	kfree(lkey_id);
	__clear_bit(id, region_12kb->used_lkey_id);
}