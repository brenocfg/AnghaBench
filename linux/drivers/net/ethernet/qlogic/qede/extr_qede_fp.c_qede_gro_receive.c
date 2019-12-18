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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int protocol; int /*<<< orphan*/  data_len; } ;
struct qede_fastpath {TYPE_2__* rxq; } ;
struct qede_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxq_id; } ;
struct TYPE_3__ {scalar_t__ gso_size; scalar_t__ gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qede_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int) ; 
 int /*<<< orphan*/  qede_gro_ip_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  qede_gro_ipv6_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  qede_skb_receive (struct qede_dev*,struct qede_fastpath*,TYPE_2__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qede_gro_receive(struct qede_dev *edev,
			     struct qede_fastpath *fp,
			     struct sk_buff *skb,
			     u16 vlan_tag)
{
	/* FW can send a single MTU sized packet from gro flow
	 * due to aggregation timeout/last segment etc. which
	 * is not expected to be a gro packet. If a skb has zero
	 * frags then simply push it in the stack as non gso skb.
	 */
	if (unlikely(!skb->data_len)) {
		skb_shinfo(skb)->gso_type = 0;
		skb_shinfo(skb)->gso_size = 0;
		goto send_skb;
	}

#ifdef CONFIG_INET
	if (skb_shinfo(skb)->gso_size) {
		skb_reset_network_header(skb);

		switch (skb->protocol) {
		case htons(ETH_P_IP):
			qede_gro_ip_csum(skb);
			break;
		case htons(ETH_P_IPV6):
			qede_gro_ipv6_csum(skb);
			break;
		default:
			DP_ERR(edev,
			       "Error: FW GRO supports only IPv4/IPv6, not 0x%04x\n",
			       ntohs(skb->protocol));
		}
	}
#endif

send_skb:
	skb_record_rx_queue(skb, fp->rxq->rxq_id);
	qede_skb_receive(edev, fp, fp->rxq, skb, vlan_tag);
}