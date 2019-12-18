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
typedef  scalar_t__ u32 ;
struct mlxsw_sp_qdisc_ops {scalar_t__ type; int (* check_params ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ;int (* replace ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ;int /*<<< orphan*/  (* unoffload ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ;int /*<<< orphan*/  (* clean_stats ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ;} ;
struct mlxsw_sp_qdisc {scalar_t__ handle; struct mlxsw_sp_qdisc_ops* ops; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_qdisc_destroy (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 
 int stub1 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ; 
 int stub2 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ; 
 int /*<<< orphan*/  stub3 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 
 int /*<<< orphan*/  stub4 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,void*) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_replace(struct mlxsw_sp_port *mlxsw_sp_port, u32 handle,
		       struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
		       struct mlxsw_sp_qdisc_ops *ops, void *params)
{
	int err;

	if (mlxsw_sp_qdisc->ops && mlxsw_sp_qdisc->ops->type != ops->type)
		/* In case this location contained a different qdisc of the
		 * same type we can override the old qdisc configuration.
		 * Otherwise, we need to remove the old qdisc before setting the
		 * new one.
		 */
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	err = ops->check_params(mlxsw_sp_port, mlxsw_sp_qdisc, params);
	if (err)
		goto err_bad_param;

	err = ops->replace(mlxsw_sp_port, mlxsw_sp_qdisc, params);
	if (err)
		goto err_config;

	if (mlxsw_sp_qdisc->handle != handle) {
		mlxsw_sp_qdisc->ops = ops;
		if (ops->clean_stats)
			ops->clean_stats(mlxsw_sp_port, mlxsw_sp_qdisc);
	}

	mlxsw_sp_qdisc->handle = handle;
	return 0;

err_bad_param:
err_config:
	if (mlxsw_sp_qdisc->handle == handle && ops->unoffload)
		ops->unoffload(mlxsw_sp_port, mlxsw_sp_qdisc, params);

	mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	return err;
}