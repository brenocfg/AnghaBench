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
struct nfp_port {int /*<<< orphan*/  tc_offload_cnt; } ;
struct nfp_flower_priv {int /*<<< orphan*/  flow_table; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct nfp_fl_payload {int /*<<< orphan*/  fl_node; int /*<<< orphan*/  unmasked_data; int /*<<< orphan*/  mask_data; int /*<<< orphan*/  action_data; TYPE_2__ pre_tun_rule; int /*<<< orphan*/  in_hw; scalar_t__ nfp_tun_ipv4_addr; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; TYPE_1__ common; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_FLOW_DEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_flower_del_linked_merge_flows (struct nfp_app*,struct nfp_fl_payload*) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_table_params ; 
 int nfp_flower_xmit_flow (struct nfp_app*,struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 int nfp_flower_xmit_pre_tun_del_flow (struct nfp_app*,struct nfp_fl_payload*) ; 
 int nfp_modify_flow_metadata (struct nfp_app*,struct nfp_fl_payload*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  nfp_tunnel_del_ipv4_off (struct nfp_app*,scalar_t__) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_del_offload(struct nfp_app *app, struct net_device *netdev,
		       struct flow_cls_offload *flow)
{
	struct nfp_flower_priv *priv = app->priv;
	struct netlink_ext_ack *extack = NULL;
	struct nfp_fl_payload *nfp_flow;
	struct nfp_port *port = NULL;
	int err;

	extack = flow->common.extack;
	if (nfp_netdev_is_nfp_repr(netdev))
		port = nfp_port_from_netdev(netdev);

	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	if (!nfp_flow) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot remove flow that does not exist");
		return -ENOENT;
	}

	err = nfp_modify_flow_metadata(app, nfp_flow);
	if (err)
		goto err_free_merge_flow;

	if (nfp_flow->nfp_tun_ipv4_addr)
		nfp_tunnel_del_ipv4_off(app, nfp_flow->nfp_tun_ipv4_addr);

	if (!nfp_flow->in_hw) {
		err = 0;
		goto err_free_merge_flow;
	}

	if (nfp_flow->pre_tun_rule.dev)
		err = nfp_flower_xmit_pre_tun_del_flow(app, nfp_flow);
	else
		err = nfp_flower_xmit_flow(app, nfp_flow,
					   NFP_FLOWER_CMSG_TYPE_FLOW_DEL);
	/* Fall through on error. */

err_free_merge_flow:
	nfp_flower_del_linked_merge_flows(app, nfp_flow);
	if (port)
		port->tc_offload_cnt--;
	kfree(nfp_flow->action_data);
	kfree(nfp_flow->mask_data);
	kfree(nfp_flow->unmasked_data);
	WARN_ON_ONCE(rhashtable_remove_fast(&priv->flow_table,
					    &nfp_flow->fl_node,
					    nfp_flower_table_params));
	kfree_rcu(nfp_flow, rcu);
	return err;
}