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
struct nfp_tun_pre_tun_rule {int /*<<< orphan*/  port_idx; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  host_ctx_id; } ;
struct nfp_tun_offloaded_mac {int /*<<< orphan*/  index; } ;
struct nfp_flower_priv {scalar_t__ pre_tun_rule_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_idx; int /*<<< orphan*/  vlan_tci; struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_ctx_id; } ;
struct nfp_fl_payload {TYPE_2__ pre_tun_rule; TYPE_1__ meta; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_PRE_TUN_RULE ; 
 scalar_t__ NFP_TUN_PRE_TUN_RULE_LIMIT ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_tun_pre_tun_rule*,int /*<<< orphan*/ ,int) ; 
 int nfp_flower_xmit_tun_conf (struct nfp_app*,int /*<<< orphan*/ ,int,unsigned char*,int /*<<< orphan*/ ) ; 
 struct nfp_tun_offloaded_mac* nfp_tunnel_lookup_offloaded_macs (struct nfp_app*,int /*<<< orphan*/ ) ; 

int nfp_flower_xmit_pre_tun_flow(struct nfp_app *app,
				 struct nfp_fl_payload *flow)
{
	struct nfp_flower_priv *app_priv = app->priv;
	struct nfp_tun_offloaded_mac *mac_entry;
	struct nfp_tun_pre_tun_rule payload;
	struct net_device *internal_dev;
	int err;

	if (app_priv->pre_tun_rule_cnt == NFP_TUN_PRE_TUN_RULE_LIMIT)
		return -ENOSPC;

	memset(&payload, 0, sizeof(struct nfp_tun_pre_tun_rule));

	internal_dev = flow->pre_tun_rule.dev;
	payload.vlan_tci = flow->pre_tun_rule.vlan_tci;
	payload.host_ctx_id = flow->meta.host_ctx_id;

	/* Lookup MAC index for the pre-tunnel rule egress device.
	 * Note that because the device is always an internal port, it will
	 * have a constant global index so does not need to be tracked.
	 */
	mac_entry = nfp_tunnel_lookup_offloaded_macs(app,
						     internal_dev->dev_addr);
	if (!mac_entry)
		return -ENOENT;

	payload.port_idx = cpu_to_be16(mac_entry->index);

	/* Copy mac id and vlan to flow - dev may not exist at delete time. */
	flow->pre_tun_rule.vlan_tci = payload.vlan_tci;
	flow->pre_tun_rule.port_idx = payload.port_idx;

	err = nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_PRE_TUN_RULE,
				       sizeof(struct nfp_tun_pre_tun_rule),
				       (unsigned char *)&payload, GFP_KERNEL);
	if (err)
		return err;

	app_priv->pre_tun_rule_cnt++;

	return 0;
}