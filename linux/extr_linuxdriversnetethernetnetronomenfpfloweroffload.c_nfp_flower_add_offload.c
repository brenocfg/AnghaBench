#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tc_cls_flower_offload {int /*<<< orphan*/  cookie; } ;
struct nfp_port {int /*<<< orphan*/  tc_offload_cnt; } ;
struct nfp_flower_priv {int /*<<< orphan*/  flow_table; } ;
struct nfp_fl_payload {struct nfp_fl_payload* unmasked_data; struct nfp_fl_payload* mask_data; struct nfp_fl_payload* action_data; int /*<<< orphan*/  link; int /*<<< orphan*/  tc_flower_cookie; struct net_device* ingress_dev; scalar_t__ ingress_offload; } ;
struct nfp_fl_key_ls {struct nfp_fl_key_ls* unmasked_data; struct nfp_fl_key_ls* mask_data; struct nfp_fl_key_ls* action_data; int /*<<< orphan*/  link; int /*<<< orphan*/  tc_flower_cookie; struct net_device* ingress_dev; scalar_t__ ingress_offload; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_FLOW_ADD ; 
 int /*<<< orphan*/  NFP_FL_STATS_CTX_DONT_CARE ; 
 int NFP_FL_TUNNEL_NONE ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_fl_payload*) ; 
 struct nfp_fl_payload* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nfp_compile_flow_metadata (struct nfp_app*,struct tc_cls_flower_offload*,struct nfp_fl_payload*,struct net_device*) ; 
 struct nfp_fl_payload* nfp_flower_allocate_new (struct nfp_fl_payload*,int) ; 
 int nfp_flower_calculate_key_layers (struct nfp_app*,struct nfp_fl_payload*,struct tc_cls_flower_offload*,int,int*) ; 
 int nfp_flower_compile_action (struct nfp_app*,struct tc_cls_flower_offload*,struct net_device*,struct nfp_fl_payload*) ; 
 int nfp_flower_compile_flow_match (struct tc_cls_flower_offload*,struct nfp_fl_payload*,struct net_device*,struct nfp_fl_payload*,int) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int nfp_flower_xmit_flow (struct net_device*,struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

__attribute__((used)) static int
nfp_flower_add_offload(struct nfp_app *app, struct net_device *netdev,
		       struct tc_cls_flower_offload *flow, bool egress)
{
	enum nfp_flower_tun_type tun_type = NFP_FL_TUNNEL_NONE;
	struct nfp_port *port = nfp_port_from_netdev(netdev);
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_payload *flow_pay;
	struct nfp_fl_key_ls *key_layer;
	struct net_device *ingr_dev;
	int err;

	ingr_dev = egress ? NULL : netdev;
	flow_pay = nfp_flower_search_fl_table(app, flow->cookie, ingr_dev,
					      NFP_FL_STATS_CTX_DONT_CARE);
	if (flow_pay) {
		/* Ignore as duplicate if it has been added by different cb. */
		if (flow_pay->ingress_offload && egress)
			return 0;
		else
			return -EOPNOTSUPP;
	}

	key_layer = kmalloc(sizeof(*key_layer), GFP_KERNEL);
	if (!key_layer)
		return -ENOMEM;

	err = nfp_flower_calculate_key_layers(app, key_layer, flow, egress,
					      &tun_type);
	if (err)
		goto err_free_key_ls;

	flow_pay = nfp_flower_allocate_new(key_layer, egress);
	if (!flow_pay) {
		err = -ENOMEM;
		goto err_free_key_ls;
	}

	flow_pay->ingress_dev = egress ? NULL : netdev;

	err = nfp_flower_compile_flow_match(flow, key_layer, netdev, flow_pay,
					    tun_type);
	if (err)
		goto err_destroy_flow;

	err = nfp_flower_compile_action(app, flow, netdev, flow_pay);
	if (err)
		goto err_destroy_flow;

	err = nfp_compile_flow_metadata(app, flow, flow_pay,
					flow_pay->ingress_dev);
	if (err)
		goto err_destroy_flow;

	err = nfp_flower_xmit_flow(netdev, flow_pay,
				   NFP_FLOWER_CMSG_TYPE_FLOW_ADD);
	if (err)
		goto err_destroy_flow;

	INIT_HLIST_NODE(&flow_pay->link);
	flow_pay->tc_flower_cookie = flow->cookie;
	hash_add_rcu(priv->flow_table, &flow_pay->link, flow->cookie);
	port->tc_offload_cnt++;

	/* Deallocate flow payload when flower rule has been destroyed. */
	kfree(key_layer);

	return 0;

err_destroy_flow:
	kfree(flow_pay->action_data);
	kfree(flow_pay->mask_data);
	kfree(flow_pay->unmasked_data);
	kfree(flow_pay);
err_free_key_ls:
	kfree(key_layer);
	return err;
}