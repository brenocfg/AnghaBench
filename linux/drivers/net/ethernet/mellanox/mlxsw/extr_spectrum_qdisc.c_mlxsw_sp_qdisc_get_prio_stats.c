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
struct tc_qopt_offload_stats {TYPE_2__* qstats; int /*<<< orphan*/  bstats; } ;
struct rtnl_link_stats64 {scalar_t__ tx_packets; scalar_t__ tx_bytes; } ;
struct mlxsw_sp_qdisc_stats {scalar_t__ tx_packets; scalar_t__ tx_bytes; scalar_t__ drops; scalar_t__ backlog; } ;
struct mlxsw_sp_qdisc {struct mlxsw_sp_qdisc_stats stats_base; } ;
struct mlxsw_sp_port_xstats {scalar_t__* backlog; scalar_t__* wred_drop; scalar_t__* tail_drop; } ;
struct TYPE_3__ {struct rtnl_link_stats64 stats; struct mlxsw_sp_port_xstats xstats; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  mlxsw_sp; TYPE_1__ periodic_hw_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog; int /*<<< orphan*/  drops; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  _bstats_update (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ mlxsw_sp_cells_bytes (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_get_prio_stats(struct mlxsw_sp_port *mlxsw_sp_port,
			      struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      struct tc_qopt_offload_stats *stats_ptr)
{
	u64 tx_bytes, tx_packets, drops = 0, backlog = 0;
	struct mlxsw_sp_qdisc_stats *stats_base;
	struct mlxsw_sp_port_xstats *xstats;
	struct rtnl_link_stats64 *stats;
	int i;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats = &mlxsw_sp_port->periodic_hw_stats.stats;
	stats_base = &mlxsw_sp_qdisc->stats_base;

	tx_bytes = stats->tx_bytes - stats_base->tx_bytes;
	tx_packets = stats->tx_packets - stats_base->tx_packets;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		drops += xstats->tail_drop[i];
		drops += xstats->wred_drop[i];
		backlog += xstats->backlog[i];
	}
	drops = drops - stats_base->drops;

	_bstats_update(stats_ptr->bstats, tx_bytes, tx_packets);
	stats_ptr->qstats->drops += drops;
	stats_ptr->qstats->backlog +=
				mlxsw_sp_cells_bytes(mlxsw_sp_port->mlxsw_sp,
						     backlog) -
				mlxsw_sp_cells_bytes(mlxsw_sp_port->mlxsw_sp,
						     stats_base->backlog);
	stats_base->backlog = backlog;
	stats_base->drops += drops;
	stats_base->tx_bytes += tx_bytes;
	stats_base->tx_packets += tx_packets;
	return 0;
}