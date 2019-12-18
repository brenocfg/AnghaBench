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
struct sk_buff {int dummy; } ;
struct mlx5e_swp_spec {scalar_t__ l3_proto; scalar_t__ l4_proto; scalar_t__ tun_l3_proto; int tun_l4_proto; scalar_t__ is_tun; } ;
struct mlx5_wqe_eth_seg {int swp_outer_l3_offset; int swp_outer_l4_offset; int swp_inner_l3_offset; int swp_inner_l4_offset; int /*<<< orphan*/  swp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_INNER_L3_IPV6 ; 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_INNER_L4_UDP ; 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_OUTER_L3_IPV6 ; 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_OUTER_L4_UDP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int skb_inner_network_offset (struct sk_buff*) ; 
 int skb_inner_transport_offset (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static inline void
mlx5e_set_eseg_swp(struct sk_buff *skb, struct mlx5_wqe_eth_seg *eseg,
		   struct mlx5e_swp_spec *swp_spec)
{
	/* SWP offsets are in 2-bytes words */
	eseg->swp_outer_l3_offset = skb_network_offset(skb) / 2;
	if (swp_spec->l3_proto == htons(ETH_P_IPV6))
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_OUTER_L3_IPV6;
	if (swp_spec->l4_proto) {
		eseg->swp_outer_l4_offset = skb_transport_offset(skb) / 2;
		if (swp_spec->l4_proto == IPPROTO_UDP)
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_OUTER_L4_UDP;
	}

	if (swp_spec->is_tun) {
		eseg->swp_inner_l3_offset = skb_inner_network_offset(skb) / 2;
		if (swp_spec->tun_l3_proto == htons(ETH_P_IPV6))
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
	} else { /* typically for ipsec when xfrm mode != XFRM_MODE_TUNNEL */
		eseg->swp_inner_l3_offset = skb_network_offset(skb) / 2;
		if (swp_spec->l3_proto == htons(ETH_P_IPV6))
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
	}
	switch (swp_spec->tun_l4_proto) {
	case IPPROTO_UDP:
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L4_UDP;
		/* fall through */
	case IPPROTO_TCP:
		eseg->swp_inner_l4_offset = skb_inner_transport_offset(skb) / 2;
		break;
	}
}