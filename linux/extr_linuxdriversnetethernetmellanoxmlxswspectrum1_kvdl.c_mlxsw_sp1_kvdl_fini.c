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
struct mlxsw_sp1_kvdl {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_LINEAR ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE ; 
 int /*<<< orphan*/  devlink_resource_occ_get_unregister (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_kvdl_parts_fini (struct mlxsw_sp1_kvdl*) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp1_kvdl_fini(struct mlxsw_sp *mlxsw_sp, void *priv)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	struct mlxsw_sp1_kvdl *kvdl = priv;

	devlink_resource_occ_get_unregister(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS);
	devlink_resource_occ_get_unregister(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS);
	devlink_resource_occ_get_unregister(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE);
	devlink_resource_occ_get_unregister(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR);
	mlxsw_sp1_kvdl_parts_fini(kvdl);
}