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
struct mlxsw_sp_acl_tcam_region {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_ctcam_region {struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_move (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void mlxsw_sp_acl_ctcam_region_parman_move(void *priv,
						  unsigned long from_index,
						  unsigned long to_index,
						  unsigned long count)
{
	struct mlxsw_sp_acl_ctcam_region *cregion = priv;
	struct mlxsw_sp_acl_tcam_region *region = cregion->region;
	struct mlxsw_sp *mlxsw_sp = region->mlxsw_sp;

	mlxsw_sp_acl_ctcam_region_move(mlxsw_sp, region,
				       from_index, to_index, count);
}