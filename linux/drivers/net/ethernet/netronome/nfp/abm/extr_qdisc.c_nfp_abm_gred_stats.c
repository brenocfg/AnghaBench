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
typedef  int /*<<< orphan*/  u32 ;
struct tc_gred_qopt_offload_stats {int /*<<< orphan*/ * xstats; int /*<<< orphan*/ * qstats; int /*<<< orphan*/ * bstats; } ;
struct TYPE_4__ {unsigned int num_bands; TYPE_1__* band; } ;
struct nfp_qdisc {scalar_t__ offloaded; TYPE_2__ red; } ;
struct nfp_abm_link {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xstats; int /*<<< orphan*/  prev_xstats; int /*<<< orphan*/  stats; int /*<<< orphan*/  prev_stats; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct nfp_qdisc* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_stats_calculate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_abm_stats_red_calculate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_stats_update (struct nfp_abm_link*) ; 

__attribute__((used)) static int
nfp_abm_gred_stats(struct nfp_abm_link *alink, u32 handle,
		   struct tc_gred_qopt_offload_stats *stats)
{
	struct nfp_qdisc *qdisc;
	unsigned int i;

	nfp_abm_stats_update(alink);

	qdisc = nfp_abm_qdisc_find(alink, handle);
	if (!qdisc)
		return -EOPNOTSUPP;
	/* If the qdisc offload has stopped we may need to adjust the backlog
	 * counters back so carry on even if qdisc is not currently offloaded.
	 */

	for (i = 0; i < qdisc->red.num_bands; i++) {
		if (!stats->xstats[i])
			continue;

		nfp_abm_stats_calculate(&qdisc->red.band[i].stats,
					&qdisc->red.band[i].prev_stats,
					&stats->bstats[i], &stats->qstats[i]);
		qdisc->red.band[i].prev_stats = qdisc->red.band[i].stats;

		nfp_abm_stats_red_calculate(&qdisc->red.band[i].xstats,
					    &qdisc->red.band[i].prev_xstats,
					    stats->xstats[i]);
		qdisc->red.band[i].prev_xstats = qdisc->red.band[i].xstats;
	}

	return qdisc->offloaded ? 0 : -EOPNOTSUPP;
}