#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {scalar_t__ protocol; } ;
struct TYPE_2__ {int nr_frags; scalar_t__ gso_type; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int MAX_TX_BUF_LEN ; 
 int MAX_TX_BUF_SHIFT ; 
 scalar_t__ SKB_GSO_TCPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff const*) ; 
 scalar_t__ skb_is_gso (struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 
 int skb_transport_offset (struct sk_buff const*) ; 
 int tcp_hdrlen (struct sk_buff const*) ; 

__attribute__((used)) static u16 atl1e_cal_tdp_req(const struct sk_buff *skb)
{
	int i = 0;
	u16 tpd_req = 1;
	u16 fg_size = 0;
	u16 proto_hdr_len = 0;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		fg_size = skb_frag_size(&skb_shinfo(skb)->frags[i]);
		tpd_req += ((fg_size + MAX_TX_BUF_LEN - 1) >> MAX_TX_BUF_SHIFT);
	}

	if (skb_is_gso(skb)) {
		if (skb->protocol == htons(ETH_P_IP) ||
		   (skb_shinfo(skb)->gso_type == SKB_GSO_TCPV6)) {
			proto_hdr_len = skb_transport_offset(skb) +
					tcp_hdrlen(skb);
			if (proto_hdr_len < skb_headlen(skb)) {
				tpd_req += ((skb_headlen(skb) - proto_hdr_len +
					   MAX_TX_BUF_LEN - 1) >>
					   MAX_TX_BUF_SHIFT);
			}
		}

	}
	return tpd_req;
}