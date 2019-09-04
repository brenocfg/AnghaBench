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
struct tc_qopt_offload_stats {TYPE_1__* qstats; int /*<<< orphan*/  bstats; } ;
struct nfp_alink_stats {scalar_t__ drops; scalar_t__ overlimits; scalar_t__ backlog_bytes; scalar_t__ backlog_pkts; scalar_t__ tx_pkts; scalar_t__ tx_bytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  drops; int /*<<< orphan*/  overlimits; int /*<<< orphan*/  backlog; int /*<<< orphan*/  qlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bstats_update (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
nfp_abm_update_stats(struct nfp_alink_stats *new, struct nfp_alink_stats *old,
		     struct tc_qopt_offload_stats *stats)
{
	_bstats_update(stats->bstats, new->tx_bytes - old->tx_bytes,
		       new->tx_pkts - old->tx_pkts);
	stats->qstats->qlen += new->backlog_pkts - old->backlog_pkts;
	stats->qstats->backlog += new->backlog_bytes - old->backlog_bytes;
	stats->qstats->overlimits += new->overlimits - old->overlimits;
	stats->qstats->drops += new->drops - old->drops;
}