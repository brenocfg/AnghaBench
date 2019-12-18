#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_qdisc {TYPE_1__* ops; int /*<<< orphan*/  handle; } ;
struct mlxsw_sp_port {int dummy; } ;
struct TYPE_2__ {int (* destroy ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_UNSPEC ; 
 int stub1 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_destroy(struct mlxsw_sp_port *mlxsw_sp_port,
		       struct mlxsw_sp_qdisc *mlxsw_sp_qdisc)
{
	int err = 0;

	if (!mlxsw_sp_qdisc)
		return 0;

	if (mlxsw_sp_qdisc->ops && mlxsw_sp_qdisc->ops->destroy)
		err = mlxsw_sp_qdisc->ops->destroy(mlxsw_sp_port,
						   mlxsw_sp_qdisc);

	mlxsw_sp_qdisc->handle = TC_H_UNSPEC;
	mlxsw_sp_qdisc->ops = NULL;
	return err;
}