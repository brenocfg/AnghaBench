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
struct mlxsw_sp_acl_tcam_chunk {int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_region_detach (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_chunk_deassoc(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam_chunk *chunk)
{
	struct mlxsw_sp_acl_tcam_region *region = chunk->region;

	list_del(&chunk->list);
	if (list_empty(&region->chunk_list)) {
		mlxsw_sp_acl_tcam_group_region_detach(mlxsw_sp, region);
		mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, region);
	}
}