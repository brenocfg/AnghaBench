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
struct tc_red_qopt_offload {int /*<<< orphan*/  stats; } ;
struct nfp_alink_stats {int dummy; } ;
struct nfp_abm_link {scalar_t__ parent; TYPE_1__* qdiscs; } ;
struct TYPE_2__ {struct nfp_alink_stats stats; } ;

/* Variables and functions */
 scalar_t__ TC_H_ROOT ; 
 int nfp_abm_ctrl_read_q_stats (struct nfp_abm_link*,int,struct nfp_alink_stats*) ; 
 int nfp_abm_ctrl_read_stats (struct nfp_abm_link*,struct nfp_alink_stats*) ; 
 int nfp_abm_red_find (struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 
 int /*<<< orphan*/  nfp_abm_update_stats (struct nfp_alink_stats*,struct nfp_alink_stats*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_abm_red_stats(struct nfp_abm_link *alink, struct tc_red_qopt_offload *opt)
{
	struct nfp_alink_stats *prev_stats;
	struct nfp_alink_stats stats;
	int i, err;

	i = nfp_abm_red_find(alink, opt);
	if (i < 0)
		return i;
	prev_stats = &alink->qdiscs[i].stats;

	if (alink->parent == TC_H_ROOT)
		err = nfp_abm_ctrl_read_stats(alink, &stats);
	else
		err = nfp_abm_ctrl_read_q_stats(alink, i, &stats);
	if (err)
		return err;

	nfp_abm_update_stats(&stats, prev_stats, &opt->stats);

	*prev_stats = stats;

	return 0;
}