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
typedef  scalar_t__ u8 ;
struct xfrm_offload {scalar_t__ proto; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct mlx5_wqe_eth_seg {int swp_outer_l3_offset; int swp_inner_l3_offset; int swp_inner_l4_offset; int /*<<< orphan*/  swp_flags; } ;
struct TYPE_4__ {scalar_t__ protocol; } ;
struct TYPE_3__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_IPV6 ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_INNER_L3_IPV6 ; 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_INNER_L4_UDP ; 
 int /*<<< orphan*/  MLX5_ETH_WQE_SWP_OUTER_L3_IPV6 ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* inner_ip_hdr (struct sk_buff*) ; 
 TYPE_1__* inner_ipv6_hdr (struct sk_buff*) ; 
 int skb_inner_network_offset (struct sk_buff*) ; 
 int skb_inner_transport_offset (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static void mlx5e_ipsec_set_swp(struct sk_buff *skb,
				struct mlx5_wqe_eth_seg *eseg, u8 mode,
				struct xfrm_offload *xo)
{
	u8 proto;

	/* Tunnel Mode:
	 * SWP:      OutL3       InL3  InL4
	 * Pkt: MAC  IP     ESP  IP    L4
	 *
	 * Transport Mode:
	 * SWP:      OutL3       InL4
	 *           InL3
	 * Pkt: MAC  IP     ESP  L4
	 *
	 * Offsets are in 2-byte words, counting from start of frame
	 */
	eseg->swp_outer_l3_offset = skb_network_offset(skb) / 2;
	if (skb->protocol == htons(ETH_P_IPV6))
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_OUTER_L3_IPV6;

	if (mode == XFRM_MODE_TUNNEL) {
		eseg->swp_inner_l3_offset = skb_inner_network_offset(skb) / 2;
		if (xo->proto == IPPROTO_IPV6) {
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
			proto = inner_ipv6_hdr(skb)->nexthdr;
		} else {
			proto = inner_ip_hdr(skb)->protocol;
		}
	} else {
		eseg->swp_inner_l3_offset = skb_network_offset(skb) / 2;
		if (skb->protocol == htons(ETH_P_IPV6))
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
		proto = xo->proto;
	}
	switch (proto) {
	case IPPROTO_UDP:
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L4_UDP;
		/* Fall through */
	case IPPROTO_TCP:
		eseg->swp_inner_l4_offset = skb_inner_transport_offset(skb) / 2;
		break;
	}
}