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
union rdma_network_hdr {int /*<<< orphan*/  ibgrh; int /*<<< orphan*/  roce4grh; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct rxe_pkt_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 struct sk_buff* PKT_TO_SKB (struct rxe_pkt_info*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union rdma_network_hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void build_rdma_network_hdr(union rdma_network_hdr *hdr,
				   struct rxe_pkt_info *pkt)
{
	struct sk_buff *skb = PKT_TO_SKB(pkt);

	memset(hdr, 0, sizeof(*hdr));
	if (skb->protocol == htons(ETH_P_IP))
		memcpy(&hdr->roce4grh, ip_hdr(skb), sizeof(hdr->roce4grh));
	else if (skb->protocol == htons(ETH_P_IPV6))
		memcpy(&hdr->ibgrh, ipv6_hdr(skb), sizeof(hdr->ibgrh));
}