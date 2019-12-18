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
typedef  int u16 ;
struct sk_buff {scalar_t__ ooo_okay; int /*<<< orphan*/  sk; } ;
struct net_device {int real_num_tx_queues; } ;

/* Variables and functions */
 int netvsc_get_tx_queue (struct net_device*,struct sk_buff*,int) ; 
 int sk_tx_queue_get (int /*<<< orphan*/ ) ; 
 int skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 

__attribute__((used)) static u16 netvsc_pick_tx(struct net_device *ndev, struct sk_buff *skb)
{
	int q_idx = sk_tx_queue_get(skb->sk);

	if (q_idx < 0 || skb->ooo_okay || q_idx >= ndev->real_num_tx_queues) {
		/* If forwarding a packet, we use the recorded queue when
		 * available for better cache locality.
		 */
		if (skb_rx_queue_recorded(skb))
			q_idx = skb_get_rx_queue(skb);
		else
			q_idx = netvsc_get_tx_queue(ndev, skb, q_idx);
	}

	return q_idx;
}