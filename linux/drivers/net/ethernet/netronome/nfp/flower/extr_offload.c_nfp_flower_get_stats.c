#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct nfp_flower_priv {int /*<<< orphan*/  stats_lock; TYPE_3__* stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_ctx_id; } ;
struct nfp_fl_payload {int /*<<< orphan*/  linked_flows; TYPE_2__ meta; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {int /*<<< orphan*/  stats; int /*<<< orphan*/  cookie; TYPE_1__ common; } ;
struct TYPE_6__ {scalar_t__ bytes; scalar_t__ pkts; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_stats_update (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_update_merge_stats (struct nfp_app*,struct nfp_fl_payload*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_flower_get_stats(struct nfp_app *app, struct net_device *netdev,
		     struct flow_cls_offload *flow)
{
	struct nfp_flower_priv *priv = app->priv;
	struct netlink_ext_ack *extack = NULL;
	struct nfp_fl_payload *nfp_flow;
	u32 ctx_id;

	extack = flow->common.extack;
	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	if (!nfp_flow) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot dump stats for flow that does not exist");
		return -EINVAL;
	}

	ctx_id = be32_to_cpu(nfp_flow->meta.host_ctx_id);

	spin_lock_bh(&priv->stats_lock);
	/* If request is for a sub_flow, update stats from merged flows. */
	if (!list_empty(&nfp_flow->linked_flows))
		nfp_flower_update_merge_stats(app, nfp_flow);

	flow_stats_update(&flow->stats, priv->stats[ctx_id].bytes,
			  priv->stats[ctx_id].pkts, priv->stats[ctx_id].used);

	priv->stats[ctx_id].pkts = 0;
	priv->stats[ctx_id].bytes = 0;
	spin_unlock_bh(&priv->stats_lock);

	return 0;
}