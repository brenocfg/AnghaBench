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
struct red_stats {scalar_t__ pdrop; scalar_t__ prob_drop; scalar_t__ prob_mark; } ;
struct mlxsw_sp_qdisc_stats {scalar_t__ backlog; scalar_t__ drops; scalar_t__ overlimits; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_4__ {struct red_stats red; } ;
struct mlxsw_sp_qdisc {size_t tclass_num; int /*<<< orphan*/  prio_bitmap; TYPE_2__ xstats_base; struct mlxsw_sp_qdisc_stats stats_base; } ;
struct mlxsw_sp_port_xstats {scalar_t__* tail_drop; scalar_t__* wred_drop; scalar_t__ ecn; } ;
struct TYPE_3__ {struct mlxsw_sp_port_xstats xstats; } ;
struct mlxsw_sp_port {TYPE_1__ periodic_hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_qdisc_bstats_per_priority_get (struct mlxsw_sp_port_xstats*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_setup_tc_qdisc_red_clean_stats(struct mlxsw_sp_port *mlxsw_sp_port,
					struct mlxsw_sp_qdisc *mlxsw_sp_qdisc)
{
	u8 tclass_num = mlxsw_sp_qdisc->tclass_num;
	struct mlxsw_sp_qdisc_stats *stats_base;
	struct mlxsw_sp_port_xstats *xstats;
	struct red_stats *red_base;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats_base = &mlxsw_sp_qdisc->stats_base;
	red_base = &mlxsw_sp_qdisc->xstats_base.red;

	mlxsw_sp_qdisc_bstats_per_priority_get(xstats,
					       mlxsw_sp_qdisc->prio_bitmap,
					       &stats_base->tx_packets,
					       &stats_base->tx_bytes);
	red_base->prob_mark = xstats->ecn;
	red_base->prob_drop = xstats->wred_drop[tclass_num];
	red_base->pdrop = xstats->tail_drop[tclass_num];

	stats_base->overlimits = red_base->prob_drop + red_base->prob_mark;
	stats_base->drops = red_base->prob_drop + red_base->pdrop;

	stats_base->backlog = 0;
}