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
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  chunk_ht; } ;
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  ref_count; TYPE_1__* region; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlxsw_sp_acl_tcam_chunk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_subset (int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ; 
 struct mlxsw_sp_acl_tcam_chunk* mlxsw_sp_acl_tcam_chunk_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*,unsigned int,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_ht_params ; 
 struct mlxsw_sp_acl_tcam_chunk* rhashtable_lookup_fast (int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_chunk *
mlxsw_sp_acl_tcam_chunk_get(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_tcam_group *group,
			    unsigned int priority,
			    struct mlxsw_afk_element_usage *elusage)
{
	struct mlxsw_sp_acl_tcam_chunk *chunk;

	chunk = rhashtable_lookup_fast(&group->chunk_ht, &priority,
				       mlxsw_sp_acl_tcam_chunk_ht_params);
	if (chunk) {
		if (WARN_ON(!mlxsw_afk_key_info_subset(chunk->region->key_info,
						       elusage)))
			return ERR_PTR(-EINVAL);
		chunk->ref_count++;
		return chunk;
	}
	return mlxsw_sp_acl_tcam_chunk_create(mlxsw_sp, group,
					      priority, elusage);
}