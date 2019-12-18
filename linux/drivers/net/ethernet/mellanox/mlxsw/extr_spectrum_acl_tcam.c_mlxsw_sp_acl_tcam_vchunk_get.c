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
struct mlxsw_sp_acl_tcam_vgroup {int /*<<< orphan*/  vchunk_ht; } ;
struct mlxsw_sp_acl_tcam_vchunk {int /*<<< orphan*/  ref_count; TYPE_1__* vregion; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlxsw_sp_acl_tcam_vchunk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_subset (int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ; 
 struct mlxsw_sp_acl_tcam_vchunk* mlxsw_sp_acl_tcam_vchunk_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vgroup*,unsigned int,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_ht_params ; 
 struct mlxsw_sp_acl_tcam_vchunk* rhashtable_lookup_fast (int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_vchunk *
mlxsw_sp_acl_tcam_vchunk_get(struct mlxsw_sp *mlxsw_sp,
			     struct mlxsw_sp_acl_tcam_vgroup *vgroup,
			     unsigned int priority,
			     struct mlxsw_afk_element_usage *elusage)
{
	struct mlxsw_sp_acl_tcam_vchunk *vchunk;

	vchunk = rhashtable_lookup_fast(&vgroup->vchunk_ht, &priority,
					mlxsw_sp_acl_tcam_vchunk_ht_params);
	if (vchunk) {
		if (WARN_ON(!mlxsw_afk_key_info_subset(vchunk->vregion->key_info,
						       elusage)))
			return ERR_PTR(-EINVAL);
		vchunk->ref_count++;
		return vchunk;
	}
	return mlxsw_sp_acl_tcam_vchunk_create(mlxsw_sp, vgroup,
					       priority, elusage);
}