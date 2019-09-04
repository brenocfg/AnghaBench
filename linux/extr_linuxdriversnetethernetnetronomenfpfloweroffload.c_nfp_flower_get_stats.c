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
struct tc_cls_flower_offload {int /*<<< orphan*/  exts; int /*<<< orphan*/  cookie; } ;
struct TYPE_2__ {scalar_t__ bytes; scalar_t__ pkts; int /*<<< orphan*/  used; } ;
struct nfp_fl_payload {int /*<<< orphan*/  lock; TYPE_1__ stats; scalar_t__ ingress_offload; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFP_FL_STATS_CTX_DONT_CARE ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_stats_update (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_get_stats(struct nfp_app *app, struct net_device *netdev,
		     struct tc_cls_flower_offload *flow, bool egress)
{
	struct nfp_fl_payload *nfp_flow;
	struct net_device *ingr_dev;

	ingr_dev = egress ? NULL : netdev;
	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, ingr_dev,
					      NFP_FL_STATS_CTX_DONT_CARE);
	if (!nfp_flow)
		return -EINVAL;

	if (nfp_flow->ingress_offload && egress)
		return 0;

	spin_lock_bh(&nfp_flow->lock);
	tcf_exts_stats_update(flow->exts, nfp_flow->stats.bytes,
			      nfp_flow->stats.pkts, nfp_flow->stats.used);

	nfp_flow->stats.pkts = 0;
	nfp_flow->stats.bytes = 0;
	spin_unlock_bh(&nfp_flow->lock);

	return 0;
}