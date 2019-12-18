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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct mlxsw_sp_qdisc_stats {scalar_t__ backlog; scalar_t__ drops; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct mlxsw_sp_qdisc {struct mlxsw_sp_qdisc_stats stats_base; } ;
struct mlxsw_sp_port_xstats {scalar_t__* wred_drop; scalar_t__* tail_drop; } ;
struct TYPE_2__ {struct rtnl_link_stats64 stats; struct mlxsw_sp_port_xstats xstats; } ;
struct mlxsw_sp_port {TYPE_1__ periodic_hw_stats; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 

__attribute__((used)) static void
mlxsw_sp_setup_tc_qdisc_prio_clean_stats(struct mlxsw_sp_port *mlxsw_sp_port,
					 struct mlxsw_sp_qdisc *mlxsw_sp_qdisc)
{
	struct mlxsw_sp_qdisc_stats *stats_base;
	struct mlxsw_sp_port_xstats *xstats;
	struct rtnl_link_stats64 *stats;
	int i;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats = &mlxsw_sp_port->periodic_hw_stats.stats;
	stats_base = &mlxsw_sp_qdisc->stats_base;

	stats_base->tx_packets = stats->tx_packets;
	stats_base->tx_bytes = stats->tx_bytes;

	stats_base->drops = 0;
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		stats_base->drops += xstats->tail_drop[i];
		stats_base->drops += xstats->wred_drop[i];
	}

	mlxsw_sp_qdisc->stats_base.backlog = 0;
}