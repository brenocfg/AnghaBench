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
struct sk_buff {int len; scalar_t__ data; } ;
struct meth_private {size_t tx_write; int /*<<< orphan*/  tx_count; struct sk_buff** tx_skbs; } ;
struct TYPE_3__ {int tx_info; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 int TX_RING_ENTRIES ; 
 TYPE_2__* mace ; 
 int /*<<< orphan*/  meth_tx_1page_prepare (struct meth_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  meth_tx_2page_prepare (struct meth_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  meth_tx_short_prepare (struct meth_private*,struct sk_buff*) ; 

__attribute__((used)) static void meth_add_to_tx_ring(struct meth_private *priv, struct sk_buff *skb)
{
	/* Remember the skb, so we can free it at interrupt time */
	priv->tx_skbs[priv->tx_write] = skb;
	if (skb->len <= 120) {
		/* Whole packet fits into descriptor */
		meth_tx_short_prepare(priv, skb);
	} else if (PAGE_ALIGN((unsigned long)skb->data) !=
		   PAGE_ALIGN((unsigned long)skb->data + skb->len - 1)) {
		/* Packet crosses page boundary */
		meth_tx_2page_prepare(priv, skb);
	} else {
		/* Packet is in one page */
		meth_tx_1page_prepare(priv, skb);
	}
	priv->tx_write = (priv->tx_write + 1) & (TX_RING_ENTRIES - 1);
	mace->eth.tx_info = priv->tx_write;
	priv->tx_count++;
}