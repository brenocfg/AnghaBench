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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct ehea_port_res {TYPE_1__* port; } ;
struct ehea_cqe {int num_bytes_transfered; int status; int /*<<< orphan*/  inet_checksum_value; } ;
struct TYPE_2__ {struct ehea_port_res* port_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int EHEA_CQE_BLIND_CKSUM ; 
 int /*<<< orphan*/  csum_unfold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 

__attribute__((used)) static inline void ehea_fill_skb(struct net_device *dev,
				 struct sk_buff *skb, struct ehea_cqe *cqe,
				 struct ehea_port_res *pr)
{
	int length = cqe->num_bytes_transfered - 4;	/*remove CRC */

	skb_put(skb, length);
	skb->protocol = eth_type_trans(skb, dev);

	/* The packet was not an IPV4 packet so a complemented checksum was
	   calculated. The value is found in the Internet Checksum field. */
	if (cqe->status & EHEA_CQE_BLIND_CKSUM) {
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = csum_unfold(~cqe->inet_checksum_value);
	} else
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_record_rx_queue(skb, pr - &pr->port->port_res[0]);
}