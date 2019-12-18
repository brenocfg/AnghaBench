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
struct z8530_channel {TYPE_2__* netdevice; struct sk_buff* tx_skb; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  z8530_tx_begin (struct z8530_channel*) ; 

__attribute__((used)) static void z8530_tx_done(struct z8530_channel *c)
{
	struct sk_buff *skb;

	/* Actually this can happen.*/
	if (c->tx_skb == NULL)
		return;

	skb = c->tx_skb;
	c->tx_skb = NULL;
	z8530_tx_begin(c);
	c->netdevice->stats.tx_packets++;
	c->netdevice->stats.tx_bytes += skb->len;
	dev_consume_skb_irq(skb);
}