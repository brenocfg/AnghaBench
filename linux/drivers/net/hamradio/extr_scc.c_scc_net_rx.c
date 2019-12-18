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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct scc_channel {int /*<<< orphan*/  dev; TYPE_1__ dev_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void scc_net_rx(struct scc_channel *scc, struct sk_buff *skb)
{
	if (skb->len == 0) {
		dev_kfree_skb_irq(skb);
		return;
	}
		
	scc->dev_stat.rx_packets++;
	scc->dev_stat.rx_bytes += skb->len;

	skb->protocol = ax25_type_trans(skb, scc->dev);
	
	netif_rx(skb);
}