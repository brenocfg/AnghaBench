#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct mlxsw_sp {TYPE_1__* sb; int /*<<< orphan*/  core; } ;
struct TYPE_3__ {void* cell_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_BUFFER_SIZE ; 
 void* MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_SB_POOL_COUNT ; 
 int /*<<< orphan*/  MLXSW_SP_SB_TC_COUNT ; 
 int devlink_sb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_cpu_port_sb_cms_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_sb_mms_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_ports_fini (struct mlxsw_sp*) ; 
 int mlxsw_sp_sb_ports_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_sb_prs_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  priv_to_devlink (int /*<<< orphan*/ ) ; 

int mlxsw_sp_buffers_init(struct mlxsw_sp *mlxsw_sp)
{
	u64 sb_size;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, CELL_SIZE))
		return -EIO;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_BUFFER_SIZE))
		return -EIO;
	sb_size = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_BUFFER_SIZE);

	mlxsw_sp->sb = kzalloc(sizeof(*mlxsw_sp->sb), GFP_KERNEL);
	if (!mlxsw_sp->sb)
		return -ENOMEM;
	mlxsw_sp->sb->cell_size = MLXSW_CORE_RES_GET(mlxsw_sp->core, CELL_SIZE);

	err = mlxsw_sp_sb_ports_init(mlxsw_sp);
	if (err)
		goto err_sb_ports_init;
	err = mlxsw_sp_sb_prs_init(mlxsw_sp);
	if (err)
		goto err_sb_prs_init;
	err = mlxsw_sp_cpu_port_sb_cms_init(mlxsw_sp);
	if (err)
		goto err_sb_cpu_port_sb_cms_init;
	err = mlxsw_sp_sb_mms_init(mlxsw_sp);
	if (err)
		goto err_sb_mms_init;
	err = devlink_sb_register(priv_to_devlink(mlxsw_sp->core), 0, sb_size,
				  MLXSW_SP_SB_POOL_COUNT,
				  MLXSW_SP_SB_POOL_COUNT,
				  MLXSW_SP_SB_TC_COUNT,
				  MLXSW_SP_SB_TC_COUNT);
	if (err)
		goto err_devlink_sb_register;

	return 0;

err_devlink_sb_register:
err_sb_mms_init:
err_sb_cpu_port_sb_cms_init:
err_sb_prs_init:
	mlxsw_sp_sb_ports_fini(mlxsw_sp);
err_sb_ports_init:
	kfree(mlxsw_sp->sb);
	return err;
}