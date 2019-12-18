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
struct mlxsw_sp_acl_erp_core {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_atcam {struct mlxsw_sp_acl_erp_core* erp_core; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp_core*) ; 
 struct mlxsw_sp_acl_erp_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_erp_tables_init (struct mlxsw_sp*,struct mlxsw_sp_acl_erp_core*) ; 

int mlxsw_sp_acl_erps_init(struct mlxsw_sp *mlxsw_sp,
			   struct mlxsw_sp_acl_atcam *atcam)
{
	struct mlxsw_sp_acl_erp_core *erp_core;
	int err;

	erp_core = kzalloc(sizeof(*erp_core), GFP_KERNEL);
	if (!erp_core)
		return -ENOMEM;
	erp_core->mlxsw_sp = mlxsw_sp;
	atcam->erp_core = erp_core;

	err = mlxsw_sp_acl_erp_tables_init(mlxsw_sp, erp_core);
	if (err)
		goto err_erp_tables_init;

	return 0;

err_erp_tables_init:
	kfree(erp_core);
	return err;
}