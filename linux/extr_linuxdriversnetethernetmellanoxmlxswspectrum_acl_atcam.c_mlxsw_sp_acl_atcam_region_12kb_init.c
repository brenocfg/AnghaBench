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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp_acl_atcam_region_12kb {struct mlxsw_sp_acl_atcam_region_12kb* used_lkey_id; int /*<<< orphan*/  max_lkey_id; int /*<<< orphan*/  lkey_ht; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_atcam_region_12kb* priv; TYPE_1__* region; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_2__ {struct mlxsw_sp* mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_LARGE_KEY_ID ; 
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_atcam_region_12kb*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_lkey_id_ht_params ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_acl_atcam_region_12kb_init(struct mlxsw_sp_acl_atcam_region *aregion)
{
	struct mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	struct mlxsw_sp_acl_atcam_region_12kb *region_12kb;
	size_t alloc_size;
	u64 max_lkey_id;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_LARGE_KEY_ID))
		return -EIO;

	max_lkey_id = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_LARGE_KEY_ID);
	region_12kb = kzalloc(sizeof(*region_12kb), GFP_KERNEL);
	if (!region_12kb)
		return -ENOMEM;

	alloc_size = BITS_TO_LONGS(max_lkey_id) * sizeof(unsigned long);
	region_12kb->used_lkey_id = kzalloc(alloc_size, GFP_KERNEL);
	if (!region_12kb->used_lkey_id) {
		err = -ENOMEM;
		goto err_used_lkey_id_alloc;
	}

	err = rhashtable_init(&region_12kb->lkey_ht,
			      &mlxsw_sp_acl_atcam_lkey_id_ht_params);
	if (err)
		goto err_rhashtable_init;

	region_12kb->max_lkey_id = max_lkey_id;
	aregion->priv = region_12kb;

	return 0;

err_rhashtable_init:
	kfree(region_12kb->used_lkey_id);
err_used_lkey_id_alloc:
	kfree(region_12kb);
	return err;
}