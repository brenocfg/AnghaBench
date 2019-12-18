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
struct nfp_fl_payload {int in_hw; struct nfp_fl_payload* unmasked_data; struct nfp_fl_payload* mask_data; struct nfp_fl_payload* action_data; int /*<<< orphan*/  fl_node; TYPE_2__ pre_tun_rule; int /*<<< orphan*/  tc_flower_cookie; } ;
struct nfp_fl_key_ls {int in_hw; struct nfp_fl_key_ls* unmasked_data; struct nfp_fl_key_ls* mask_data; struct nfp_fl_key_ls* action_data; int /*<<< orphan*/  fl_node; TYPE_2__ pre_tun_rule; int /*<<< orphan*/  tc_flower_cookie; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; TYPE_1__ common; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_FLOW_ADD ; 
 int NFP_FL_TUNNEL_NONE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_fl_payload*) ; 
 struct nfp_fl_payload* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nfp_compile_flow_metadata (struct nfp_app*,struct flow_cls_offload*,struct nfp_fl_payload*,struct net_device*,struct netlink_ext_ack*) ; 
 struct nfp_fl_payload* nfp_flower_allocate_new (struct nfp_fl_payload*) ; 
 int nfp_flower_calculate_key_layers (struct nfp_app*,struct net_device*,struct nfp_fl_payload*,struct flow_cls_offload*,int*,struct netlink_ext_ack*) ; 
 int nfp_flower_compile_action (struct nfp_app*,struct flow_cls_offload*,struct net_device*,struct nfp_fl_payload*,struct netlink_ext_ack*) ; 
 int nfp_flower_compile_flow_match (struct nfp_app*,struct flow_cls_offload*,struct nfp_fl_payload*,struct net_device*,struct nfp_fl_payload*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nfp_flower_table_params ; 
 int nfp_flower_validate_pre_tun_rule (struct nfp_app*,struct nfp_fl_payload*,struct netlink_ext_ack*) ; 
 int nfp_flower_xmit_flow (struct nfp_app*,struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 int nfp_flower_xmit_pre_tun_flow (struct nfp_app*,struct nfp_fl_payload*) ; 
 int /*<<< orphan*/  nfp_modify_flow_metadata (struct nfp_app*,struct nfp_fl_payload*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_add_offload(struct nfp_app *app, struct net_device *netdev,
		       struct flow_cls_offload *flow)
{
	enum nfp_flower_tun_type tun_type = NFP_FL_TUNNEL_NONE;
	struct nfp_flower_priv *priv = app->priv;
	struct netlink_ext_ack *extack = NULL;
	struct nfp_fl_payload *flow_pay;
	struct nfp_fl_key_ls *key_layer;
	struct nfp_port *port = NULL;
	int err;

	extack = flow->common.extack;
	if (nfp_netdev_is_nfp_repr(netdev))
		port = nfp_port_from_netdev(netdev);

	key_layer = kmalloc(sizeof(*key_layer), GFP_KERNEL);
	if (!key_layer)
		return -ENOMEM;

	err = nfp_flower_calculate_key_layers(app, netdev, key_layer, flow,
					      &tun_type, extack);
	if (err)
		goto err_free_key_ls;

	flow_pay = nfp_flower_allocate_new(key_layer);
	if (!flow_pay) {
		err = -ENOMEM;
		goto err_free_key_ls;
	}

	err = nfp_flower_compile_flow_match(app, flow, key_layer, netdev,
					    flow_pay, tun_type, extack);
	if (err)
		goto err_destroy_flow;

	err = nfp_flower_compile_action(app, flow, netdev, flow_pay, extack);
	if (err)
		goto err_destroy_flow;

	if (flow_pay->pre_tun_rule.dev) {
		err = nfp_flower_validate_pre_tun_rule(app, flow_pay, extack);
		if (err)
			goto err_destroy_flow;
	}

	err = nfp_compile_flow_metadata(app, flow, flow_pay, netdev, extack);
	if (err)
		goto err_destroy_flow;

	flow_pay->tc_flower_cookie = flow->cookie;
	err = rhashtable_insert_fast(&priv->flow_table, &flow_pay->fl_node,
				     nfp_flower_table_params);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot insert flow into tables for offloads");
		goto err_release_metadata;
	}

	if (flow_pay->pre_tun_rule.dev)
		err = nfp_flower_xmit_pre_tun_flow(app, flow_pay);
	else
		err = nfp_flower_xmit_flow(app, flow_pay,
					   NFP_FLOWER_CMSG_TYPE_FLOW_ADD);
	if (err)
		goto err_remove_rhash;

	if (port)
		port->tc_offload_cnt++;

	flow_pay->in_hw = true;

	/* Deallocate flow payload when flower rule has been destroyed. */
	kfree(key_layer);

	return 0;

err_remove_rhash:
	WARN_ON_ONCE(rhashtable_remove_fast(&priv->flow_table,
					    &flow_pay->fl_node,
					    nfp_flower_table_params));
err_release_metadata:
	nfp_modify_flow_metadata(app, flow_pay);
err_destroy_flow:
	kfree(flow_pay->action_data);
	kfree(flow_pay->mask_data);
	kfree(flow_pay->unmasked_data);
	kfree(flow_pay);
err_free_key_ls:
	kfree(key_layer);
	return err;
}