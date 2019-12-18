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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_flower_tp_ports {int dummy; } ;
struct nfp_flower_meta_tci {int dummy; } ;
struct nfp_flower_mac_mpls {int dummy; } ;
struct nfp_flower_ipv6 {int dummy; } ;
struct TYPE_4__ {void* dst; } ;
struct nfp_flower_ipv4_udp_tun {TYPE_2__ ipv4; } ;
struct TYPE_3__ {void* dst; } ;
struct nfp_flower_ipv4_gre_tun {TYPE_1__ ipv4; } ;
struct nfp_flower_ipv4 {int dummy; } ;
struct nfp_flower_in_port {int dummy; } ;
struct nfp_flower_ext_meta {int dummy; } ;
struct nfp_fl_payload {void* nfp_tun_ipv4_addr; int /*<<< orphan*/ * mask_data; int /*<<< orphan*/ * unmasked_data; } ;
struct nfp_fl_key_ls {int key_layer; int key_layer_two; int /*<<< orphan*/  key_size; } ;
struct nfp_app {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_cls_offload {int dummy; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;
typedef  void* __be32 ;

/* Variables and functions */
 int NFP_FLOWER_LAYER2_GENEVE ; 
 int NFP_FLOWER_LAYER2_GENEVE_OP ; 
 int NFP_FLOWER_LAYER2_GRE ; 
 int NFP_FLOWER_LAYER_EXT_META ; 
 int NFP_FLOWER_LAYER_IPV4 ; 
 int NFP_FLOWER_LAYER_IPV6 ; 
 int NFP_FLOWER_LAYER_MAC ; 
 int NFP_FLOWER_LAYER_TP ; 
 int NFP_FLOWER_LAYER_VXLAN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_flower_compile_ext_meta (struct nfp_flower_ext_meta*,int) ; 
 int nfp_flower_compile_geneve_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv4 (struct nfp_flower_ipv4*,struct nfp_flower_ipv4*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv4_gre_tun (void*,void*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv4_udp_tun (void*,void*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv6 (struct nfp_flower_ipv6*,struct nfp_flower_ipv6*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_mac (struct nfp_flower_mac_mpls*,struct nfp_flower_mac_mpls*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_compile_meta_tci (struct nfp_flower_meta_tci*,struct nfp_flower_meta_tci*,struct flow_cls_offload*,int) ; 
 int nfp_flower_compile_port (struct nfp_flower_in_port*,int /*<<< orphan*/ ,int,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nfp_flower_compile_tport (struct nfp_flower_tp_ports*,struct nfp_flower_tp_ports*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  nfp_flower_get_port_id_from_netdev (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_tunnel_add_ipv4_off (struct nfp_app*,void*) ; 

int nfp_flower_compile_flow_match(struct nfp_app *app,
				  struct flow_cls_offload *flow,
				  struct nfp_fl_key_ls *key_ls,
				  struct net_device *netdev,
				  struct nfp_fl_payload *nfp_flow,
				  enum nfp_flower_tun_type tun_type,
				  struct netlink_ext_ack *extack)
{
	u32 port_id;
	int err;
	u8 *ext;
	u8 *msk;

	port_id = nfp_flower_get_port_id_from_netdev(app, netdev);

	memset(nfp_flow->unmasked_data, 0, key_ls->key_size);
	memset(nfp_flow->mask_data, 0, key_ls->key_size);

	ext = nfp_flow->unmasked_data;
	msk = nfp_flow->mask_data;

	nfp_flower_compile_meta_tci((struct nfp_flower_meta_tci *)ext,
				    (struct nfp_flower_meta_tci *)msk,
				    flow, key_ls->key_layer);
	ext += sizeof(struct nfp_flower_meta_tci);
	msk += sizeof(struct nfp_flower_meta_tci);

	/* Populate Extended Metadata if Required. */
	if (NFP_FLOWER_LAYER_EXT_META & key_ls->key_layer) {
		nfp_flower_compile_ext_meta((struct nfp_flower_ext_meta *)ext,
					    key_ls->key_layer_two);
		nfp_flower_compile_ext_meta((struct nfp_flower_ext_meta *)msk,
					    key_ls->key_layer_two);
		ext += sizeof(struct nfp_flower_ext_meta);
		msk += sizeof(struct nfp_flower_ext_meta);
	}

	/* Populate Exact Port data. */
	err = nfp_flower_compile_port((struct nfp_flower_in_port *)ext,
				      port_id, false, tun_type, extack);
	if (err)
		return err;

	/* Populate Mask Port Data. */
	err = nfp_flower_compile_port((struct nfp_flower_in_port *)msk,
				      port_id, true, tun_type, extack);
	if (err)
		return err;

	ext += sizeof(struct nfp_flower_in_port);
	msk += sizeof(struct nfp_flower_in_port);

	if (NFP_FLOWER_LAYER_MAC & key_ls->key_layer) {
		nfp_flower_compile_mac((struct nfp_flower_mac_mpls *)ext,
				       (struct nfp_flower_mac_mpls *)msk,
				       flow);
		ext += sizeof(struct nfp_flower_mac_mpls);
		msk += sizeof(struct nfp_flower_mac_mpls);
	}

	if (NFP_FLOWER_LAYER_TP & key_ls->key_layer) {
		nfp_flower_compile_tport((struct nfp_flower_tp_ports *)ext,
					 (struct nfp_flower_tp_ports *)msk,
					 flow);
		ext += sizeof(struct nfp_flower_tp_ports);
		msk += sizeof(struct nfp_flower_tp_ports);
	}

	if (NFP_FLOWER_LAYER_IPV4 & key_ls->key_layer) {
		nfp_flower_compile_ipv4((struct nfp_flower_ipv4 *)ext,
					(struct nfp_flower_ipv4 *)msk,
					flow);
		ext += sizeof(struct nfp_flower_ipv4);
		msk += sizeof(struct nfp_flower_ipv4);
	}

	if (NFP_FLOWER_LAYER_IPV6 & key_ls->key_layer) {
		nfp_flower_compile_ipv6((struct nfp_flower_ipv6 *)ext,
					(struct nfp_flower_ipv6 *)msk,
					flow);
		ext += sizeof(struct nfp_flower_ipv6);
		msk += sizeof(struct nfp_flower_ipv6);
	}

	if (key_ls->key_layer_two & NFP_FLOWER_LAYER2_GRE) {
		__be32 tun_dst;

		nfp_flower_compile_ipv4_gre_tun((void *)ext, (void *)msk, flow);
		tun_dst = ((struct nfp_flower_ipv4_gre_tun *)ext)->ipv4.dst;
		ext += sizeof(struct nfp_flower_ipv4_gre_tun);
		msk += sizeof(struct nfp_flower_ipv4_gre_tun);

		/* Store the tunnel destination in the rule data.
		 * This must be present and be an exact match.
		 */
		nfp_flow->nfp_tun_ipv4_addr = tun_dst;
		nfp_tunnel_add_ipv4_off(app, tun_dst);
	}

	if (key_ls->key_layer & NFP_FLOWER_LAYER_VXLAN ||
	    key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE) {
		__be32 tun_dst;

		nfp_flower_compile_ipv4_udp_tun((void *)ext, (void *)msk, flow);
		tun_dst = ((struct nfp_flower_ipv4_udp_tun *)ext)->ipv4.dst;
		ext += sizeof(struct nfp_flower_ipv4_udp_tun);
		msk += sizeof(struct nfp_flower_ipv4_udp_tun);

		/* Store the tunnel destination in the rule data.
		 * This must be present and be an exact match.
		 */
		nfp_flow->nfp_tun_ipv4_addr = tun_dst;
		nfp_tunnel_add_ipv4_off(app, tun_dst);

		if (key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE_OP) {
			err = nfp_flower_compile_geneve_opt(ext, msk, flow);
			if (err)
				return err;
		}
	}

	return 0;
}