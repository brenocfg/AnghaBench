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
struct mlxsw_sp_acl_tcam_ventry {int /*<<< orphan*/  rulei; } ;
struct mlxsw_sp_acl_tcam_ops {int (* entry_add ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ entry_priv_size; } ;
struct mlxsw_sp_acl_tcam_entry {int /*<<< orphan*/  priv; struct mlxsw_sp_acl_tcam_chunk* chunk; struct mlxsw_sp_acl_tcam_ventry* ventry; } ;
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  priv; TYPE_1__* region; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_entry*) ; 
 struct mlxsw_sp_acl_tcam_entry* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_entry *
mlxsw_sp_acl_tcam_entry_create(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_tcam_ventry *ventry,
			       struct mlxsw_sp_acl_tcam_chunk *chunk)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_entry *entry;
	int err;

	entry = kzalloc(sizeof(*entry) + ops->entry_priv_size, GFP_KERNEL);
	if (!entry)
		return ERR_PTR(-ENOMEM);
	entry->ventry = ventry;
	entry->chunk = chunk;

	err = ops->entry_add(mlxsw_sp, chunk->region->priv, chunk->priv,
			     entry->priv, ventry->rulei);
	if (err)
		goto err_entry_add;

	return entry;

err_entry_add:
	kfree(entry);
	return ERR_PTR(err);
}