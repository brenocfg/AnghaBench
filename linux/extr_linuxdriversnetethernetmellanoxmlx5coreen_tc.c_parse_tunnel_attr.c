#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct mlx5e_priv {TYPE_6__* netdev; TYPE_8__* mdev; } ;
struct mlx5_flow_spec {void* match_criteria; void* match_value; } ;
struct flow_dissector_key_ports {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_ipv6_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct flow_dissector_key_ip {int tos; int ttl; } ;
struct flow_dissector_key_control {scalar_t__ addr_type; } ;
struct TYPE_16__ {int /*<<< orphan*/  vxlan; } ;
struct TYPE_12__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_10__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_15__ {TYPE_4__ ipv6_layout; TYPE_2__ ipv4_layout; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_9__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_13__ {TYPE_3__ ipv6_layout; TYPE_1__ ipv4_layout; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_PORTS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmac_15_0 ; 
 int /*<<< orphan*/  dmac_47_16 ; 
 TYPE_7__ dst_ipv4_dst_ipv6 ; 
 int /*<<< orphan*/  ether_addr_copy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  frag ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  ip_dscp ; 
 int /*<<< orphan*/  ip_ecn ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  ipv6_layout ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_vxlan_lookup_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_6__*,char*,...) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_headers ; 
 int /*<<< orphan*/  parse_vxlan_attr (struct mlx5_flow_spec*,struct tc_cls_flower_offload*) ; 
 void* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ src_ipv4_src_ipv6 ; 
 int /*<<< orphan*/  ttl_hoplimit ; 
 int /*<<< orphan*/  udp_dport ; 
 int /*<<< orphan*/  udp_sport ; 
 int /*<<< orphan*/  vxlan_encap_decap ; 

__attribute__((used)) static int parse_tunnel_attr(struct mlx5e_priv *priv,
			     struct mlx5_flow_spec *spec,
			     struct tc_cls_flower_offload *f)
{
	void *headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				       outer_headers);
	void *headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				       outer_headers);

	struct flow_dissector_key_control *enc_control =
		skb_flow_dissector_target(f->dissector,
					  FLOW_DISSECTOR_KEY_ENC_CONTROL,
					  f->key);

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ENC_PORTS)) {
		struct flow_dissector_key_ports *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_PORTS,
						  f->key);
		struct flow_dissector_key_ports *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_PORTS,
						  f->mask);

		/* Full udp dst port must be given */
		if (memchr_inv(&mask->dst, 0xff, sizeof(mask->dst)))
			goto vxlan_match_offload_err;

		if (mlx5_vxlan_lookup_port(priv->mdev->vxlan, be16_to_cpu(key->dst)) &&
		    MLX5_CAP_ESW(priv->mdev, vxlan_encap_decap))
			parse_vxlan_attr(spec, f);
		else {
			netdev_warn(priv->netdev,
				    "%d isn't an offloaded vxlan udp dport\n", be16_to_cpu(key->dst));
			return -EOPNOTSUPP;
		}

		MLX5_SET(fte_match_set_lyr_2_4, headers_c,
			 udp_dport, ntohs(mask->dst));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v,
			 udp_dport, ntohs(key->dst));

		MLX5_SET(fte_match_set_lyr_2_4, headers_c,
			 udp_sport, ntohs(mask->src));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v,
			 udp_sport, ntohs(key->src));
	} else { /* udp dst port must be given */
vxlan_match_offload_err:
		netdev_warn(priv->netdev,
			    "IP tunnel decap offload supported only for vxlan, must set UDP dport\n");
		return -EOPNOTSUPP;
	}

	if (enc_control->addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) {
		struct flow_dissector_key_ipv4_addrs *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
						  f->key);
		struct flow_dissector_key_ipv4_addrs *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
						  f->mask);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c,
			 src_ipv4_src_ipv6.ipv4_layout.ipv4,
			 ntohl(mask->src));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v,
			 src_ipv4_src_ipv6.ipv4_layout.ipv4,
			 ntohl(key->src));

		MLX5_SET(fte_match_set_lyr_2_4, headers_c,
			 dst_ipv4_dst_ipv6.ipv4_layout.ipv4,
			 ntohl(mask->dst));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v,
			 dst_ipv4_dst_ipv6.ipv4_layout.ipv4,
			 ntohl(key->dst));

		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ethertype);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ethertype, ETH_P_IP);
	} else if (enc_control->addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) {
		struct flow_dissector_key_ipv6_addrs *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS,
						  f->key);
		struct flow_dissector_key_ipv6_addrs *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS,
						  f->mask);

		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &mask->src, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &key->src, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));

		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &mask->dst, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &key->dst, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));

		MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ethertype);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ethertype, ETH_P_IPV6);
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ENC_IP)) {
		struct flow_dissector_key_ip *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IP,
						  f->key);
		struct flow_dissector_key_ip *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_IP,
						  f->mask);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_ecn, mask->tos & 0x3);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_ecn, key->tos & 0x3);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_dscp, mask->tos >> 2);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_dscp, key->tos  >> 2);

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ttl_hoplimit, mask->ttl);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ttl_hoplimit, key->ttl);
	}

	/* Enforce DMAC when offloading incoming tunneled flows.
	 * Flow counters require a match on the DMAC.
	 */
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, dmac_47_16);
	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, dmac_15_0);
	ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				     dmac_47_16), priv->netdev->dev_addr);

	/* let software handle IP fragments */
	MLX5_SET(fte_match_set_lyr_2_4, headers_c, frag, 1);
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, frag, 0);

	return 0;
}