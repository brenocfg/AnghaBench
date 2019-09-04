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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_tcam_ops {int (* entry_add ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_rule_info*) ;} ;
struct mlxsw_sp_acl_tcam_group {int dummy; } ;
struct mlxsw_sp_acl_tcam_entry {struct mlxsw_sp_acl_tcam_chunk* chunk; int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  priv; struct mlxsw_sp_acl_tcam_region* region; } ;
struct TYPE_2__ {int /*<<< orphan*/  elusage; } ;
struct mlxsw_sp_acl_rule_info {TYPE_1__ values; int /*<<< orphan*/  priority; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_tcam_chunk*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_tcam_chunk*) ; 
 struct mlxsw_sp_acl_tcam_chunk* mlxsw_sp_acl_tcam_chunk_get (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_put (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_chunk*) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_rule_info*) ; 

__attribute__((used)) static int mlxsw_sp_acl_tcam_entry_add(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_tcam_group *group,
				       struct mlxsw_sp_acl_tcam_entry *entry,
				       struct mlxsw_sp_acl_rule_info *rulei)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_chunk *chunk;
	struct mlxsw_sp_acl_tcam_region *region;
	int err;

	chunk = mlxsw_sp_acl_tcam_chunk_get(mlxsw_sp, group, rulei->priority,
					    &rulei->values.elusage);
	if (IS_ERR(chunk))
		return PTR_ERR(chunk);

	region = chunk->region;

	err = ops->entry_add(mlxsw_sp, region->priv, chunk->priv,
			     entry->priv, rulei);
	if (err)
		goto err_entry_add;
	entry->chunk = chunk;

	return 0;

err_entry_add:
	mlxsw_sp_acl_tcam_chunk_put(mlxsw_sp, chunk);
	return err;
}