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
struct mlxsw_sp_acl_tcam_vchunk {struct mlxsw_sp_acl_tcam_chunk* chunk; struct mlxsw_sp_acl_tcam_chunk* chunk2; } ;
struct mlxsw_sp_acl_tcam_rehash_ctx {int /*<<< orphan*/ * stop_ventry; int /*<<< orphan*/ * start_ventry; struct mlxsw_sp_acl_tcam_vchunk* current_vchunk; } ;
struct mlxsw_sp_acl_tcam_region {int dummy; } ;
struct mlxsw_sp_acl_tcam_chunk {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_tcam_chunk*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_tcam_chunk*) ; 
 struct mlxsw_sp_acl_tcam_chunk* mlxsw_sp_acl_tcam_chunk_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vchunk*,struct mlxsw_sp_acl_tcam_region*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_vchunk_migrate_start(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_tcam_vchunk *vchunk,
				       struct mlxsw_sp_acl_tcam_region *region,
				       struct mlxsw_sp_acl_tcam_rehash_ctx *ctx)
{
	struct mlxsw_sp_acl_tcam_chunk *new_chunk;

	new_chunk = mlxsw_sp_acl_tcam_chunk_create(mlxsw_sp, vchunk, region);
	if (IS_ERR(new_chunk))
		return PTR_ERR(new_chunk);
	vchunk->chunk2 = vchunk->chunk;
	vchunk->chunk = new_chunk;
	ctx->current_vchunk = vchunk;
	ctx->start_ventry = NULL;
	ctx->stop_ventry = NULL;
	return 0;
}