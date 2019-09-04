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
struct bnx2x_fastpath {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_queue; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_gro_receive(struct bnx2x *bp, struct bnx2x_fastpath *fp,
			       struct sk_buff *skb)
{
#ifdef CONFIG_INET
	if (skb_shinfo(skb)->gso_size) {
		switch (be16_to_cpu(skb->protocol)) {
		case ETH_P_IP:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ip_csum);
			break;
		case ETH_P_IPV6:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ipv6_csum);
			break;
		default:
			netdev_WARN_ONCE(bp->dev,
					 "Error: FW GRO supports only IPv4/IPv6, not 0x%04x\n",
					 be16_to_cpu(skb->protocol));
		}
	}
#endif
	skb_record_rx_queue(skb, fp->rx_queue);
	napi_gro_receive(&fp->napi, skb);
}