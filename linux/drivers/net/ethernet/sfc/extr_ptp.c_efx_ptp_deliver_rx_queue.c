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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

__attribute__((used)) static void efx_ptp_deliver_rx_queue(struct sk_buff_head *q)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(q))) {
		local_bh_disable();
		netif_receive_skb(skb);
		local_bh_enable();
	}
}