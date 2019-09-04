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
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* chunk_fini ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* chunk_init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;scalar_t__ chunk_priv_size; } ;
struct mlxsw_sp_acl_tcam_group {int /*<<< orphan*/  chunk_ht; } ;
struct mlxsw_sp_acl_tcam_chunk {unsigned int priority; int ref_count; int /*<<< orphan*/  priv; int /*<<< orphan*/  ht_node; TYPE_1__* region; struct mlxsw_sp_acl_tcam_group* group; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_chunk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MLXSW_SP_ACL_TCAM_CATCHALL_PRIO ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_chunk*) ; 
 struct mlxsw_sp_acl_tcam_chunk* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_chunk_assoc (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_group*,unsigned int,struct mlxsw_afk_element_usage*,struct mlxsw_sp_acl_tcam_chunk*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_deassoc (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_chunk*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_ht_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_chunk *
mlxsw_sp_acl_tcam_chunk_create(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_tcam_group *group,
			       unsigned int priority,
			       struct mlxsw_afk_element_usage *elusage)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_chunk *chunk;
	int err;

	if (priority == MLXSW_SP_ACL_TCAM_CATCHALL_PRIO)
		return ERR_PTR(-EINVAL);

	chunk = kzalloc(sizeof(*chunk) + ops->chunk_priv_size, GFP_KERNEL);
	if (!chunk)
		return ERR_PTR(-ENOMEM);
	chunk->priority = priority;
	chunk->group = group;
	chunk->ref_count = 1;

	err = mlxsw_sp_acl_tcam_chunk_assoc(mlxsw_sp, group, priority,
					    elusage, chunk);
	if (err)
		goto err_chunk_assoc;

	ops->chunk_init(chunk->region->priv, chunk->priv, priority);

	err = rhashtable_insert_fast(&group->chunk_ht, &chunk->ht_node,
				     mlxsw_sp_acl_tcam_chunk_ht_params);
	if (err)
		goto err_rhashtable_insert;

	return chunk;

err_rhashtable_insert:
	ops->chunk_fini(chunk->priv);
	mlxsw_sp_acl_tcam_chunk_deassoc(mlxsw_sp, chunk);
err_chunk_assoc:
	kfree(chunk);
	return ERR_PTR(err);
}