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
struct tc_red_qopt_offload {TYPE_2__* xstats; } ;
struct nfp_alink_xstats {scalar_t__ pdrop; scalar_t__ ecn_marked; } ;
struct nfp_abm_link {scalar_t__ parent; TYPE_1__* qdiscs; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdrop; int /*<<< orphan*/  forced_mark; } ;
struct TYPE_3__ {struct nfp_alink_xstats xstats; } ;

/* Variables and functions */
 scalar_t__ TC_H_ROOT ; 
 int nfp_abm_ctrl_read_q_xstats (struct nfp_abm_link*,int,struct nfp_alink_xstats*) ; 
 int nfp_abm_ctrl_read_xstats (struct nfp_abm_link*,struct nfp_alink_xstats*) ; 
 int nfp_abm_red_find (struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 

__attribute__((used)) static int
nfp_abm_red_xstats(struct nfp_abm_link *alink, struct tc_red_qopt_offload *opt)
{
	struct nfp_alink_xstats *prev_xstats;
	struct nfp_alink_xstats xstats;
	int i, err;

	i = nfp_abm_red_find(alink, opt);
	if (i < 0)
		return i;
	prev_xstats = &alink->qdiscs[i].xstats;

	if (alink->parent == TC_H_ROOT)
		err = nfp_abm_ctrl_read_xstats(alink, &xstats);
	else
		err = nfp_abm_ctrl_read_q_xstats(alink, i, &xstats);
	if (err)
		return err;

	opt->xstats->forced_mark += xstats.ecn_marked - prev_xstats->ecn_marked;
	opt->xstats->pdrop += xstats.pdrop - prev_xstats->pdrop;

	*prev_xstats = xstats;

	return 0;
}