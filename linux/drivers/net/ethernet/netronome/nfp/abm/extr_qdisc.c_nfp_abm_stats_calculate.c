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
struct nfp_alink_stats {scalar_t__ drops; scalar_t__ overlimits; scalar_t__ backlog_bytes; scalar_t__ backlog_pkts; scalar_t__ tx_pkts; scalar_t__ tx_bytes; } ;
struct gnet_stats_queue {int /*<<< orphan*/  drops; int /*<<< orphan*/  overlimits; int /*<<< orphan*/  backlog; int /*<<< orphan*/  qlen; } ;
struct gnet_stats_basic_packed {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bstats_update (struct gnet_stats_basic_packed*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
nfp_abm_stats_calculate(struct nfp_alink_stats *new,
			struct nfp_alink_stats *old,
			struct gnet_stats_basic_packed *bstats,
			struct gnet_stats_queue *qstats)
{
	_bstats_update(bstats, new->tx_bytes - old->tx_bytes,
		       new->tx_pkts - old->tx_pkts);
	qstats->qlen += new->backlog_pkts - old->backlog_pkts;
	qstats->backlog += new->backlog_bytes - old->backlog_bytes;
	qstats->overlimits += new->overlimits - old->overlimits;
	qstats->drops += new->drops - old->drops;
}