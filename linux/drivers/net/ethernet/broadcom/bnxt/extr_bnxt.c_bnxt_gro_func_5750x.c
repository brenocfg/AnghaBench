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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int data; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct bnxt_tpa_info {int flags2; int /*<<< orphan*/  hdr_info; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int BNXT_TPA_INNER_L2_OFF (int /*<<< orphan*/ ) ; 
 int BNXT_TPA_INNER_L3_OFF (int /*<<< orphan*/ ) ; 
 int BNXT_TPA_OUTER_L3_OFF (int /*<<< orphan*/ ) ; 
 int ETH_HLEN ; 
 int RX_TPA_START_CMP_FLAGS2_IP_TYPE ; 
 int /*<<< orphan*/  bnxt_gro_tunnel (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *bnxt_gro_func_5750x(struct bnxt_tpa_info *tpa_info,
					   int payload_off, int tcp_ts,
					   struct sk_buff *skb)
{
#ifdef CONFIG_INET
	u16 outer_ip_off, inner_ip_off, inner_mac_off;
	u32 hdr_info = tpa_info->hdr_info;
	int iphdr_len, nw_off;

	inner_ip_off = BNXT_TPA_INNER_L3_OFF(hdr_info);
	inner_mac_off = BNXT_TPA_INNER_L2_OFF(hdr_info);
	outer_ip_off = BNXT_TPA_OUTER_L3_OFF(hdr_info);

	nw_off = inner_ip_off - ETH_HLEN;
	skb_set_network_header(skb, nw_off);
	iphdr_len = (tpa_info->flags2 & RX_TPA_START_CMP_FLAGS2_IP_TYPE) ?
		     sizeof(struct ipv6hdr) : sizeof(struct iphdr);
	skb_set_transport_header(skb, nw_off + iphdr_len);

	if (inner_mac_off) { /* tunnel */
		__be16 proto = *((__be16 *)(skb->data + outer_ip_off -
					    ETH_HLEN - 2));

		bnxt_gro_tunnel(skb, proto);
	}
#endif
	return skb;
}