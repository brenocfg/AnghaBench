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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_acl_tcam_region {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_atcam_region_12kb {int /*<<< orphan*/  lkey_ht; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_tcam_region* region; struct mlxsw_sp_acl_atcam_region_12kb* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct mlxsw_sp_acl_atcam_lkey_id_ht_key {int /*<<< orphan*/  erp_id; int /*<<< orphan*/  enc_key; TYPE_1__ member_0; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  refcnt; } ;
struct mlxsw_sp {int /*<<< orphan*/  acl; } ;
struct mlxsw_afk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_END ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_START ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlxsw_afk_clear (struct mlxsw_afk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_afk* mlxsw_sp_acl_afk (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_atcam_lkey_id* mlxsw_sp_acl_atcam_lkey_id_create (struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_lkey_id_ht_key*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_lkey_id_ht_params ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_acl_atcam_lkey_id* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_sp_acl_atcam_lkey_id_ht_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_12kb_lkey_id_get(struct mlxsw_sp_acl_atcam_region *aregion,
				    char *enc_key, u8 erp_id)
{
	struct mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	struct mlxsw_sp_acl_tcam_region *region = aregion->region;
	struct mlxsw_sp_acl_atcam_lkey_id_ht_key ht_key = {{ 0 } };
	struct mlxsw_sp *mlxsw_sp = region->mlxsw_sp;
	struct mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	struct mlxsw_sp_acl_atcam_lkey_id *lkey_id;

	memcpy(ht_key.enc_key, enc_key, sizeof(ht_key.enc_key));
	mlxsw_afk_clear(afk, ht_key.enc_key,
			MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_START,
			MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_END);
	ht_key.erp_id = erp_id;
	lkey_id = rhashtable_lookup_fast(&region_12kb->lkey_ht, &ht_key,
					 mlxsw_sp_acl_atcam_lkey_id_ht_params);
	if (lkey_id) {
		refcount_inc(&lkey_id->refcnt);
		return lkey_id;
	}

	return mlxsw_sp_acl_atcam_lkey_id_create(aregion, &ht_key);
}