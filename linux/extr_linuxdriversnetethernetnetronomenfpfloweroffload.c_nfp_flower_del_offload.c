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
struct nfp_fl_payload {int /*<<< orphan*/  unmasked_data; int /*<<< orphan*/  mask_data; int /*<<< orphan*/  action_data; int /*<<< orphan*/  link; scalar_t__ nfp_tun_ipv4_addr; } ;
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_FLOW_DEL ; 
 int /*<<< orphan*/  NFP_FL_STATS_CTX_DONT_CARE ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 struct nfp_fl_payload* nfp_flower_search_fl_table (struct nfp_app*,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int nfp_flower_xmit_flow (struct net_device*,struct nfp_fl_payload*,int /*<<< orphan*/ ) ; 
 int nfp_modify_flow_metadata (struct nfp_app*,struct nfp_fl_payload*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  nfp_tunnel_del_ipv4_off (struct nfp_app*,scalar_t__) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static int
nfp_flower_del_offload(struct nfp_app *app, struct net_device *netdev,
		       struct tc_cls_flower_offload *flow, bool egress)
{
	struct nfp_port *port = nfp_port_from_netdev(netdev);
	struct nfp_fl_payload *nfp_flow;
	struct net_device *ingr_dev;
	int err;

	ingr_dev = egress ? NULL : netdev;
	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, ingr_dev,
					      NFP_FL_STATS_CTX_DONT_CARE);
	if (!nfp_flow)
		return egress ? 0 : -ENOENT;

	err = nfp_modify_flow_metadata(app, nfp_flow);
	if (err)
		goto err_free_flow;

	if (nfp_flow->nfp_tun_ipv4_addr)
		nfp_tunnel_del_ipv4_off(app, nfp_flow->nfp_tun_ipv4_addr);

	err = nfp_flower_xmit_flow(netdev, nfp_flow,
				   NFP_FLOWER_CMSG_TYPE_FLOW_DEL);
	if (err)
		goto err_free_flow;

err_free_flow:
	hash_del_rcu(&nfp_flow->link);
	port->tc_offload_cnt--;
	kfree(nfp_flow->action_data);
	kfree(nfp_flow->mask_data);
	kfree(nfp_flow->unmasked_data);
	kfree_rcu(nfp_flow, rcu);
	return err;
}