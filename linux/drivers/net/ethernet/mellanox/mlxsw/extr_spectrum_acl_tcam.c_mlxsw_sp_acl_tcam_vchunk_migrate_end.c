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
struct mlxsw_sp_acl_tcam_vchunk {int /*<<< orphan*/ * chunk2; } ;
struct mlxsw_sp_acl_tcam_rehash_ctx {int /*<<< orphan*/ * current_vchunk; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_destroy (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vchunk_migrate_end(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp_acl_tcam_vchunk *vchunk,
				     struct mlxsw_sp_acl_tcam_rehash_ctx *ctx)
{
	mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk2);
	vchunk->chunk2 = NULL;
	ctx->current_vchunk = NULL;
}