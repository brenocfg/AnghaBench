#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  min; int /*<<< orphan*/  is_ecn; scalar_t__ limit; } ;
struct tc_red_qopt_offload {TYPE_3__ set; int /*<<< orphan*/  handle; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int num_bands; TYPE_1__* band; } ;
struct nfp_qdisc {int use_cnt; TYPE_2__ red; scalar_t__ params_ok; TYPE_4__** children; } ;
struct nfp_abm_link {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  use_cnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  threshold; int /*<<< orphan*/  ecn; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_QDISC_RED ; 
 TYPE_4__* NFP_QDISC_UNTRACKED ; 
 scalar_t__ nfp_abm_qdisc_child_valid (struct nfp_qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 
 int nfp_abm_qdisc_replace (struct net_device*,struct nfp_abm_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nfp_qdisc**) ; 
 scalar_t__ nfp_abm_red_check_params (struct nfp_abm_link*,struct tc_red_qopt_offload*) ; 

__attribute__((used)) static int
nfp_abm_red_replace(struct net_device *netdev, struct nfp_abm_link *alink,
		    struct tc_red_qopt_offload *opt)
{
	struct nfp_qdisc *qdisc;
	int ret;

	ret = nfp_abm_qdisc_replace(netdev, alink, NFP_QDISC_RED, opt->parent,
				    opt->handle, 1, &qdisc);
	if (ret < 0)
		return ret;

	/* If limit != 0 child gets reset */
	if (opt->set.limit) {
		if (nfp_abm_qdisc_child_valid(qdisc, 0))
			qdisc->children[0]->use_cnt--;
		qdisc->children[0] = NULL;
	} else {
		/* Qdisc was just allocated without a limit will use noop_qdisc,
		 * i.e. a block hole.
		 */
		if (!ret)
			qdisc->children[0] = NFP_QDISC_UNTRACKED;
	}

	qdisc->params_ok = nfp_abm_red_check_params(alink, opt);
	if (qdisc->params_ok) {
		qdisc->red.num_bands = 1;
		qdisc->red.band[0].ecn = opt->set.is_ecn;
		qdisc->red.band[0].threshold = opt->set.min;
	}

	if (qdisc->use_cnt == 1)
		nfp_abm_qdisc_offload_update(alink);

	return 0;
}