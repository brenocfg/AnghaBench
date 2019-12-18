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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct iphdr {scalar_t__ frag_off; } ;
struct atl1e_recv_ret_status {int pkt_flag; int err_flag; } ;
struct atl1e_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_HLEN ; 
 int RRS_ERR_IP_CSUM ; 
 int RRS_ERR_L4_CSUM ; 
 int RRS_IS_802_3 ; 
 int RRS_IS_IPV4 ; 
 int RRS_IS_IPV6 ; 
 int RRS_IS_IP_DF ; 
 int RRS_IS_TCP ; 
 int RRS_IS_UDP ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void atl1e_rx_checksum(struct atl1e_adapter *adapter,
		  struct sk_buff *skb, struct atl1e_recv_ret_status *prrs)
{
	u8 *packet = (u8 *)(prrs + 1);
	struct iphdr *iph;
	u16 head_len = ETH_HLEN;
	u16 pkt_flags;
	u16 err_flags;

	skb_checksum_none_assert(skb);
	pkt_flags = prrs->pkt_flag;
	err_flags = prrs->err_flag;
	if (((pkt_flags & RRS_IS_IPV4) || (pkt_flags & RRS_IS_IPV6)) &&
		((pkt_flags & RRS_IS_TCP) || (pkt_flags & RRS_IS_UDP))) {
		if (pkt_flags & RRS_IS_IPV4) {
			if (pkt_flags & RRS_IS_802_3)
				head_len += 8;
			iph = (struct iphdr *) (packet + head_len);
			if (iph->frag_off != 0 && !(pkt_flags & RRS_IS_IP_DF))
				goto hw_xsum;
		}
		if (!(err_flags & (RRS_ERR_IP_CSUM | RRS_ERR_L4_CSUM))) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			return;
		}
	}

hw_xsum :
	return;
}