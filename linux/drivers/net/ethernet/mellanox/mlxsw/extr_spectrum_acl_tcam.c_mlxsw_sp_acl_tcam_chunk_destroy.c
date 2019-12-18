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
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_chunk*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_chunk_destroy(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam_chunk *chunk)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->chunk_fini(chunk->priv);
	kfree(chunk);
}