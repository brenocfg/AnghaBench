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
typedef  size_t u8 ;
struct red_stats {int prob_drop; int prob_mark; int pdrop; } ;
struct TYPE_3__ {struct red_stats red; } ;
struct mlxsw_sp_qdisc {size_t tclass_num; TYPE_1__ xstats_base; } ;
struct mlxsw_sp_port_xstats {int* wred_drop; int ecn; int* tail_drop; } ;
struct TYPE_4__ {struct mlxsw_sp_port_xstats xstats; } ;
struct mlxsw_sp_port {TYPE_2__ periodic_hw_stats; } ;

/* Variables and functions */

__attribute__((used)) static int
mlxsw_sp_qdisc_get_red_xstats(struct mlxsw_sp_port *mlxsw_sp_port,
			      struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      void *xstats_ptr)
{
	struct red_stats *xstats_base = &mlxsw_sp_qdisc->xstats_base.red;
	u8 tclass_num = mlxsw_sp_qdisc->tclass_num;
	struct mlxsw_sp_port_xstats *xstats;
	struct red_stats *res = xstats_ptr;
	int early_drops, marks, pdrops;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;

	early_drops = xstats->wred_drop[tclass_num] - xstats_base->prob_drop;
	marks = xstats->ecn - xstats_base->prob_mark;
	pdrops = xstats->tail_drop[tclass_num] - xstats_base->pdrop;

	res->pdrop += pdrops;
	res->prob_drop += early_drops;
	res->prob_mark += marks;

	xstats_base->pdrop += pdrops;
	xstats_base->prob_drop += early_drops;
	xstats_base->prob_mark += marks;
	return 0;
}