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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  chunk_list; } ;
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  tcam; } ;
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_tcam_region*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_tcam_group_region_attach (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*,struct mlxsw_sp_acl_tcam_region*) ; 
 struct mlxsw_sp_acl_tcam_region* mlxsw_sp_acl_tcam_group_region_find (struct mlxsw_sp_acl_tcam_group*,unsigned int,struct mlxsw_afk_element_usage*,int*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_use_patterns (struct mlxsw_sp_acl_tcam_group*,struct mlxsw_afk_element_usage*,struct mlxsw_afk_element_usage*) ; 
 struct mlxsw_sp_acl_tcam_region* mlxsw_sp_acl_tcam_region_create (struct mlxsw_sp*,int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_chunk_assoc(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_acl_tcam_group *group,
			      unsigned int priority,
			      struct mlxsw_afk_element_usage *elusage,
			      struct mlxsw_sp_acl_tcam_chunk *chunk)
{
	struct mlxsw_sp_acl_tcam_region *region;
	bool region_created = false;
	bool need_split;
	int err;

	region = mlxsw_sp_acl_tcam_group_region_find(group, priority, elusage,
						     &need_split);
	if (region && need_split) {
		/* According to priority, the chunk should belong to an
		 * existing region. However, this chunk needs elements
		 * that region does not contain. We need to split the existing
		 * region into two and create a new region for this chunk
		 * in between. This is not supported now.
		 */
		return -EOPNOTSUPP;
	}
	if (!region) {
		struct mlxsw_afk_element_usage region_elusage;

		mlxsw_sp_acl_tcam_group_use_patterns(group, elusage,
						     &region_elusage);
		region = mlxsw_sp_acl_tcam_region_create(mlxsw_sp, group->tcam,
							 &region_elusage);
		if (IS_ERR(region))
			return PTR_ERR(region);
		region_created = true;
	}

	chunk->region = region;
	list_add_tail(&chunk->list, &region->chunk_list);

	if (!region_created)
		return 0;

	err = mlxsw_sp_acl_tcam_group_region_attach(mlxsw_sp, group, region);
	if (err)
		goto err_group_region_attach;

	return 0;

err_group_region_attach:
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, region);
	return err;
}