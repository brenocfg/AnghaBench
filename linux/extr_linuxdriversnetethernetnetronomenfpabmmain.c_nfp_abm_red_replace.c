#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* qstats; int /*<<< orphan*/  min; int /*<<< orphan*/  is_ecn; int /*<<< orphan*/  max; } ;
struct tc_red_qopt_offload {scalar_t__ parent; int /*<<< orphan*/  handle; TYPE_4__ set; } ;
struct nfp_abm_link {scalar_t__ parent; TYPE_5__* qdiscs; TYPE_2__* abm; } ;
struct net_device {int dummy; } ;
struct TYPE_13__ {scalar_t__ backlog_bytes; scalar_t__ backlog_pkts; } ;
struct TYPE_12__ {TYPE_6__ stats; int /*<<< orphan*/  xstats; int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  backlog; int /*<<< orphan*/  qlen; } ;
struct TYPE_9__ {TYPE_1__* app; } ;
struct TYPE_8__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 int TC_H_MIN (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 int __nfp_abm_reset_root (struct net_device*,struct nfp_abm_link*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int nfp_abm_ctrl_read_q_stats (struct nfp_abm_link*,int,TYPE_6__*) ; 
 int nfp_abm_ctrl_read_q_xstats (struct nfp_abm_link*,int,int /*<<< orphan*/ *) ; 
 int nfp_abm_ctrl_read_stats (struct nfp_abm_link*,TYPE_6__*) ; 
 int nfp_abm_ctrl_read_xstats (struct nfp_abm_link*,int /*<<< orphan*/ *) ; 
 int nfp_abm_ctrl_set_all_q_lvls (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int nfp_abm_ctrl_set_q_lvl (struct nfp_abm_link*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_red_destroy (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int nfp_abm_red_find (struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nfp_abm_red_replace(struct net_device *netdev, struct nfp_abm_link *alink,
		    struct tc_red_qopt_offload *opt)
{
	bool existing;
	int i, err;

	i = nfp_abm_red_find(alink, opt);
	existing = i >= 0;

	if (opt->set.min != opt->set.max || !opt->set.is_ecn) {
		nfp_warn(alink->abm->app->cpp,
			 "RED offload failed - unsupported parameters\n");
		err = -EINVAL;
		goto err_destroy;
	}

	if (existing) {
		if (alink->parent == TC_H_ROOT)
			err = nfp_abm_ctrl_set_all_q_lvls(alink, opt->set.min);
		else
			err = nfp_abm_ctrl_set_q_lvl(alink, i, opt->set.min);
		if (err)
			goto err_destroy;
		return 0;
	}

	if (opt->parent == TC_H_ROOT) {
		i = 0;
		err = __nfp_abm_reset_root(netdev, alink, TC_H_ROOT, 1,
					   opt->set.min);
	} else if (TC_H_MAJ(alink->parent) == TC_H_MAJ(opt->parent)) {
		i = TC_H_MIN(opt->parent) - 1;
		err = nfp_abm_ctrl_set_q_lvl(alink, i, opt->set.min);
	} else {
		return -EINVAL;
	}
	/* Set the handle to try full clean up, in case IO failed */
	alink->qdiscs[i].handle = opt->handle;
	if (err)
		goto err_destroy;

	if (opt->parent == TC_H_ROOT)
		err = nfp_abm_ctrl_read_stats(alink, &alink->qdiscs[i].stats);
	else
		err = nfp_abm_ctrl_read_q_stats(alink, i,
						&alink->qdiscs[i].stats);
	if (err)
		goto err_destroy;

	if (opt->parent == TC_H_ROOT)
		err = nfp_abm_ctrl_read_xstats(alink,
					       &alink->qdiscs[i].xstats);
	else
		err = nfp_abm_ctrl_read_q_xstats(alink, i,
						 &alink->qdiscs[i].xstats);
	if (err)
		goto err_destroy;

	alink->qdiscs[i].stats.backlog_pkts = 0;
	alink->qdiscs[i].stats.backlog_bytes = 0;

	return 0;
err_destroy:
	/* If the qdisc keeps on living, but we can't offload undo changes */
	if (existing) {
		opt->set.qstats->qlen -= alink->qdiscs[i].stats.backlog_pkts;
		opt->set.qstats->backlog -=
			alink->qdiscs[i].stats.backlog_bytes;
	}
	nfp_abm_red_destroy(netdev, alink, opt->handle);

	return err;
}