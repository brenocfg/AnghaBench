#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct tc_prio_qopt_offload_params {TYPE_2__* qstats; } ;
struct TYPE_3__ {int /*<<< orphan*/  backlog; } ;
struct mlxsw_sp_qdisc {TYPE_1__ stats_base; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  mlxsw_sp; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog; } ;

/* Variables and functions */
 scalar_t__ mlxsw_sp_cells_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_qdisc_prio_unoffload(struct mlxsw_sp_port *mlxsw_sp_port,
			      struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      void *params)
{
	struct tc_prio_qopt_offload_params *p = params;
	u64 backlog;

	backlog = mlxsw_sp_cells_bytes(mlxsw_sp_port->mlxsw_sp,
				       mlxsw_sp_qdisc->stats_base.backlog);
	p->qstats->backlog -= backlog;
}