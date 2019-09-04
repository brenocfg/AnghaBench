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
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* chunk_fini ) (int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  chunk_ht; } ;
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  priv; int /*<<< orphan*/  ht_node; struct mlxsw_sp_acl_tcam_group* group; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_chunk*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_deassoc (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_chunk*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_chunk_destroy(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam_chunk *chunk)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_group *group = chunk->group;

	rhashtable_remove_fast(&group->chunk_ht, &chunk->ht_node,
			       mlxsw_sp_acl_tcam_chunk_ht_params);
	ops->chunk_fini(chunk->priv);
	mlxsw_sp_acl_tcam_chunk_deassoc(mlxsw_sp, chunk);
	kfree(chunk);
}