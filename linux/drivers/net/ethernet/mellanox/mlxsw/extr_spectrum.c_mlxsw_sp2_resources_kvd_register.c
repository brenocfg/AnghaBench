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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_core {int dummy; } ;
struct devlink_resource_size_params {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_RESOURCE_ID_PARENT_TOP ; 
 int /*<<< orphan*/  DEVLINK_RESOURCE_UNIT_ENTRY ; 
 int EIO ; 
 int /*<<< orphan*/  KVD_SIZE ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_KVD_GRANULARITY ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_KVD ; 
 int /*<<< orphan*/  MLXSW_SP_RESOURCE_NAME_KVD ; 
 int devlink_resource_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devlink_resource_size_params*) ; 
 int /*<<< orphan*/  devlink_resource_size_params_init (struct devlink_resource_size_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct devlink* priv_to_devlink (struct mlxsw_core*) ; 

__attribute__((used)) static int mlxsw_sp2_resources_kvd_register(struct mlxsw_core *mlxsw_core)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_core);
	struct devlink_resource_size_params kvd_size_params;
	u32 kvd_size;

	if (!MLXSW_CORE_RES_VALID(mlxsw_core, KVD_SIZE))
		return -EIO;

	kvd_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE);
	devlink_resource_size_params_init(&kvd_size_params, kvd_size, kvd_size,
					  MLXSW_SP_KVD_GRANULARITY,
					  DEVLINK_RESOURCE_UNIT_ENTRY);

	return devlink_resource_register(devlink, MLXSW_SP_RESOURCE_NAME_KVD,
					 kvd_size, MLXSW_SP_RESOURCE_KVD,
					 DEVLINK_RESOURCE_ID_PARENT_TOP,
					 &kvd_size_params);
}