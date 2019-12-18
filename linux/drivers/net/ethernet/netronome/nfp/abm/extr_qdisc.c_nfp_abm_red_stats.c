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
struct tc_qopt_offload_stats {int /*<<< orphan*/  qstats; int /*<<< orphan*/  bstats; } ;
struct TYPE_4__ {TYPE_1__* band; } ;
struct nfp_qdisc {scalar_t__ offloaded; TYPE_2__ red; } ;
struct nfp_abm_link {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  prev_stats; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct nfp_qdisc* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_stats_calculate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_stats_update (struct nfp_abm_link*) ; 

__attribute__((used)) static int
nfp_abm_red_stats(struct nfp_abm_link *alink, u32 handle,
		  struct tc_qopt_offload_stats *stats)
{
	struct nfp_qdisc *qdisc;

	nfp_abm_stats_update(alink);

	qdisc = nfp_abm_qdisc_find(alink, handle);
	if (!qdisc)
		return -EOPNOTSUPP;
	/* If the qdisc offload has stopped we may need to adjust the backlog
	 * counters back so carry on even if qdisc is not currently offloaded.
	 */

	nfp_abm_stats_calculate(&qdisc->red.band[0].stats,
				&qdisc->red.band[0].prev_stats,
				stats->bstats, stats->qstats);
	qdisc->red.band[0].prev_stats = qdisc->red.band[0].stats;

	return qdisc->offloaded ? 0 : -EOPNOTSUPP;
}