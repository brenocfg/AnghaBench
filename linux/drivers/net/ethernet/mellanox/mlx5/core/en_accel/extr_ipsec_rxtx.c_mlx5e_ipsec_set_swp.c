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
struct sk_buff {void* protocol; } ;
struct mlx5e_swp_spec {int is_tun; scalar_t__ tun_l4_proto; void* tun_l3_proto; void* l3_proto; } ;
struct mlx5_wqe_eth_seg {int dummy; } ;
struct TYPE_4__ {scalar_t__ protocol; } ;
struct TYPE_3__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_IPV6 ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* inner_ip_hdr (struct sk_buff*) ; 
 TYPE_1__* inner_ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  mlx5e_set_eseg_swp (struct sk_buff*,struct mlx5_wqe_eth_seg*,struct mlx5e_swp_spec*) ; 

__attribute__((used)) static void mlx5e_ipsec_set_swp(struct sk_buff *skb,
				struct mlx5_wqe_eth_seg *eseg, u8 mode,
				struct xfrm_offload *xo)
{
	struct mlx5e_swp_spec swp_spec = {};

	/* Tunnel Mode:
	 * SWP:      OutL3       InL3  InL4
	 * Pkt: MAC  IP     ESP  IP    L4
	 *
	 * Transport Mode:
	 * SWP:      OutL3       InL4
	 *           InL3
	 * Pkt: MAC  IP     ESP  L4
	 */
	swp_spec.l3_proto = skb->protocol;
	swp_spec.is_tun = mode == XFRM_MODE_TUNNEL;
	if (swp_spec.is_tun) {
		if (xo->proto == IPPROTO_IPV6) {
			swp_spec.tun_l3_proto = htons(ETH_P_IPV6);
			swp_spec.tun_l4_proto = inner_ipv6_hdr(skb)->nexthdr;
		} else {
			swp_spec.tun_l3_proto = htons(ETH_P_IP);
			swp_spec.tun_l4_proto = inner_ip_hdr(skb)->protocol;
		}
	} else {
		swp_spec.tun_l3_proto = skb->protocol;
		swp_spec.tun_l4_proto = xo->proto;
	}

	mlx5e_set_eseg_swp(skb, eseg, &swp_spec);
}