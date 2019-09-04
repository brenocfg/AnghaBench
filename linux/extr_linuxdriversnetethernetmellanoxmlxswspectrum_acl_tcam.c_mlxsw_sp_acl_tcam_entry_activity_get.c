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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_tcam_ops {int (* entry_activity_get ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct mlxsw_sp_acl_tcam_entry {int /*<<< orphan*/  priv; struct mlxsw_sp_acl_tcam_chunk* chunk; } ;
struct mlxsw_sp_acl_tcam_chunk {struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_entry_activity_get(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp_acl_tcam_entry *entry,
				     bool *activity)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_chunk *chunk = entry->chunk;
	struct mlxsw_sp_acl_tcam_region *region = chunk->region;

	return ops->entry_activity_get(mlxsw_sp, region->priv,
				       entry->priv, activity);
}