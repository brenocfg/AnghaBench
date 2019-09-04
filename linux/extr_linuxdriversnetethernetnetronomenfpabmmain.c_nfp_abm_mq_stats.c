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
struct tc_mq_qopt_offload {int /*<<< orphan*/  stats; } ;
struct nfp_alink_stats {int dummy; } ;
struct nfp_abm_link {unsigned int num_qdiscs; TYPE_1__* qdiscs; } ;
struct TYPE_2__ {scalar_t__ handle; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 scalar_t__ TC_H_UNSPEC ; 
 int nfp_abm_ctrl_read_q_stats (struct nfp_abm_link*,unsigned int,struct nfp_alink_stats*) ; 
 int /*<<< orphan*/  nfp_abm_update_stats (struct nfp_alink_stats*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_abm_mq_stats(struct nfp_abm_link *alink, struct tc_mq_qopt_offload *opt)
{
	struct nfp_alink_stats stats;
	unsigned int i;
	int err;

	for (i = 0; i < alink->num_qdiscs; i++) {
		if (alink->qdiscs[i].handle == TC_H_UNSPEC)
			continue;

		err = nfp_abm_ctrl_read_q_stats(alink, i, &stats);
		if (err)
			return err;

		nfp_abm_update_stats(&stats, &alink->qdiscs[i].stats,
				     &opt->stats);
	}

	return 0;
}