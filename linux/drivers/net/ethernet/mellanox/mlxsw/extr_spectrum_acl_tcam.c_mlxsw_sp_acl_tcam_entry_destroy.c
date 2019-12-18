#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* entry_del ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_tcam_entry {int /*<<< orphan*/  priv; TYPE_2__* chunk; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; TYPE_1__* region; } ;
struct TYPE_3__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_entry*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_acl_tcam_entry_destroy(struct mlxsw_sp *mlxsw_sp,
					    struct mlxsw_sp_acl_tcam_entry *entry)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->entry_del(mlxsw_sp, entry->chunk->region->priv,
		       entry->chunk->priv, entry->priv);
	kfree(entry);
}