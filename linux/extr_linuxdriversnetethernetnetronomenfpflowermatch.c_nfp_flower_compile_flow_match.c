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
typedef  int /*<<< orphan*/  u8 ;
struct tc_cls_flower_offload {int dummy; } ;
struct nfp_repr {int /*<<< orphan*/  app; } ;
struct nfp_flower_tp_ports {int dummy; } ;
struct nfp_flower_meta_tci {int dummy; } ;
struct nfp_flower_mac_mpls {int dummy; } ;
struct nfp_flower_ipv6 {int dummy; } ;
struct nfp_flower_ipv4_udp_tun {int /*<<< orphan*/  ip_dst; } ;
struct nfp_flower_ipv4 {int dummy; } ;
struct nfp_flower_in_port {int dummy; } ;
struct nfp_flower_ext_meta {int dummy; } ;
struct nfp_fl_payload {int /*<<< orphan*/  nfp_tun_ipv4_addr; int /*<<< orphan*/ * mask_data; int /*<<< orphan*/ * unmasked_data; } ;
struct nfp_fl_key_ls {int key_layer; int key_layer_two; int /*<<< orphan*/  key_size; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFP_FLOWER_LAYER2_GENEVE ; 
 int NFP_FLOWER_LAYER2_GENEVE_OP ; 
 int NFP_FLOWER_LAYER_EXT_META ; 
 int NFP_FLOWER_LAYER_IPV4 ; 
 int NFP_FLOWER_LAYER_IPV6 ; 
 int NFP_FLOWER_LAYER_MAC ; 
 int NFP_FLOWER_LAYER_TP ; 
 int NFP_FLOWER_LAYER_VXLAN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_compile_ext_meta (struct nfp_flower_ext_meta*,int) ; 
 int nfp_flower_compile_geneve_opt (int /*<<< orphan*/ *,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv4 (struct nfp_flower_ipv4*,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv4_udp_tun (void*,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_ipv6 (struct nfp_flower_ipv6*,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_mac (struct nfp_flower_mac_mpls*,struct tc_cls_flower_offload*,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_meta_tci (struct nfp_flower_meta_tci*,struct tc_cls_flower_offload*,int,int) ; 
 int nfp_flower_compile_port (struct nfp_flower_in_port*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nfp_flower_compile_tport (struct nfp_flower_tp_ports*,struct tc_cls_flower_offload*,int) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int /*<<< orphan*/  nfp_repr_get_port_id (struct net_device*) ; 
 int /*<<< orphan*/  nfp_tunnel_add_ipv4_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_tunnel_write_macs (int /*<<< orphan*/ ) ; 

int nfp_flower_compile_flow_match(struct tc_cls_flower_offload *flow,
				  struct nfp_fl_key_ls *key_ls,
				  struct net_device *netdev,
				  struct nfp_fl_payload *nfp_flow,
				  enum nfp_flower_tun_type tun_type)
{
	struct nfp_repr *netdev_repr;
	int err;
	u8 *ext;
	u8 *msk;

	memset(nfp_flow->unmasked_data, 0, key_ls->key_size);
	memset(nfp_flow->mask_data, 0, key_ls->key_size);

	ext = nfp_flow->unmasked_data;
	msk = nfp_flow->mask_data;

	/* Populate Exact Metadata. */
	nfp_flower_compile_meta_tci((struct nfp_flower_meta_tci *)ext,
				    flow, key_ls->key_layer, false);
	/* Populate Mask Metadata. */
	nfp_flower_compile_meta_tci((struct nfp_flower_meta_tci *)msk,
				    flow, key_ls->key_layer, true);
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
				      nfp_repr_get_port_id(netdev),
				      false, tun_type);
	if (err)
		return err;

	/* Populate Mask Port Data. */
	err = nfp_flower_compile_port((struct nfp_flower_in_port *)msk,
				      nfp_repr_get_port_id(netdev),
				      true, tun_type);
	if (err)
		return err;

	ext += sizeof(struct nfp_flower_in_port);
	msk += sizeof(struct nfp_flower_in_port);

	if (NFP_FLOWER_LAYER_MAC & key_ls->key_layer) {
		/* Populate Exact MAC Data. */
		nfp_flower_compile_mac((struct nfp_flower_mac_mpls *)ext,
				       flow, false);
		/* Populate Mask MAC Data. */
		nfp_flower_compile_mac((struct nfp_flower_mac_mpls *)msk,
				       flow, true);
		ext += sizeof(struct nfp_flower_mac_mpls);
		msk += sizeof(struct nfp_flower_mac_mpls);
	}

	if (NFP_FLOWER_LAYER_TP & key_ls->key_layer) {
		/* Populate Exact TP Data. */
		nfp_flower_compile_tport((struct nfp_flower_tp_ports *)ext,
					 flow, false);
		/* Populate Mask TP Data. */
		nfp_flower_compile_tport((struct nfp_flower_tp_ports *)msk,
					 flow, true);
		ext += sizeof(struct nfp_flower_tp_ports);
		msk += sizeof(struct nfp_flower_tp_ports);
	}

	if (NFP_FLOWER_LAYER_IPV4 & key_ls->key_layer) {
		/* Populate Exact IPv4 Data. */
		nfp_flower_compile_ipv4((struct nfp_flower_ipv4 *)ext,
					flow, false);
		/* Populate Mask IPv4 Data. */
		nfp_flower_compile_ipv4((struct nfp_flower_ipv4 *)msk,
					flow, true);
		ext += sizeof(struct nfp_flower_ipv4);
		msk += sizeof(struct nfp_flower_ipv4);
	}

	if (NFP_FLOWER_LAYER_IPV6 & key_ls->key_layer) {
		/* Populate Exact IPv4 Data. */
		nfp_flower_compile_ipv6((struct nfp_flower_ipv6 *)ext,
					flow, false);
		/* Populate Mask IPv4 Data. */
		nfp_flower_compile_ipv6((struct nfp_flower_ipv6 *)msk,
					flow, true);
		ext += sizeof(struct nfp_flower_ipv6);
		msk += sizeof(struct nfp_flower_ipv6);
	}

	if (key_ls->key_layer & NFP_FLOWER_LAYER_VXLAN ||
	    key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE) {
		__be32 tun_dst;

		/* Populate Exact VXLAN Data. */
		nfp_flower_compile_ipv4_udp_tun((void *)ext, flow, false);
		/* Populate Mask VXLAN Data. */
		nfp_flower_compile_ipv4_udp_tun((void *)msk, flow, true);
		tun_dst = ((struct nfp_flower_ipv4_udp_tun *)ext)->ip_dst;
		ext += sizeof(struct nfp_flower_ipv4_udp_tun);
		msk += sizeof(struct nfp_flower_ipv4_udp_tun);

		/* Configure tunnel end point MAC. */
		if (nfp_netdev_is_nfp_repr(netdev)) {
			netdev_repr = netdev_priv(netdev);
			nfp_tunnel_write_macs(netdev_repr->app);

			/* Store the tunnel destination in the rule data.
			 * This must be present and be an exact match.
			 */
			nfp_flow->nfp_tun_ipv4_addr = tun_dst;
			nfp_tunnel_add_ipv4_off(netdev_repr->app, tun_dst);
		}

		if (key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE_OP) {
			err = nfp_flower_compile_geneve_opt(ext, flow, false);
			if (err)
				return err;

			err = nfp_flower_compile_geneve_opt(msk, flow, true);
			if (err)
				return err;
		}
	}

	return 0;
}