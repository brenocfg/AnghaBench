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
struct TYPE_2__ {scalar_t__ backlog; } ;
struct mlxsw_sp_qdisc {int /*<<< orphan*/  tclass_num; TYPE_1__ stats_base; } ;
struct mlxsw_sp_port {struct mlxsw_sp_qdisc* root_qdisc; } ;

/* Variables and functions */
 int mlxsw_sp_tclass_congestion_disable (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_red_destroy(struct mlxsw_sp_port *mlxsw_sp_port,
			   struct mlxsw_sp_qdisc *mlxsw_sp_qdisc)
{
	struct mlxsw_sp_qdisc *root_qdisc = mlxsw_sp_port->root_qdisc;

	if (root_qdisc != mlxsw_sp_qdisc)
		root_qdisc->stats_base.backlog -=
					mlxsw_sp_qdisc->stats_base.backlog;

	return mlxsw_sp_tclass_congestion_disable(mlxsw_sp_port,
						  mlxsw_sp_qdisc->tclass_num);
}