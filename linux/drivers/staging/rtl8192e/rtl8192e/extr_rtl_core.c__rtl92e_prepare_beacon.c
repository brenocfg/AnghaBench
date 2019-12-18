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
struct tx_desc {int OWN; } ;
struct sk_buff {scalar_t__ cb; } ;
struct rtl8192_tx_ring {int /*<<< orphan*/  queue; struct tx_desc* desc; } ;
struct r8192_priv {TYPE_1__* ops; TYPE_2__* rtllib; struct rtl8192_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;
struct cb_desc {size_t queue_index; int data_rate; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_headroom; struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_fill_descriptor ) (struct net_device*,struct tx_desc*,struct cb_desc*,struct sk_buff*) ;} ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* rtllib_get_beacon (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct tx_desc*,struct cb_desc*,struct sk_buff*) ; 

__attribute__((used)) static void _rtl92e_prepare_beacon(struct r8192_priv *priv)
{
	struct net_device *dev = priv->rtllib->dev;
	struct sk_buff *pskb = NULL, *pnewskb = NULL;
	struct cb_desc *tcb_desc = NULL;
	struct rtl8192_tx_ring *ring = NULL;
	struct tx_desc *pdesc = NULL;

	ring = &priv->tx_ring[BEACON_QUEUE];
	pskb = __skb_dequeue(&ring->queue);
	kfree_skb(pskb);

	pnewskb = rtllib_get_beacon(priv->rtllib);
	if (!pnewskb)
		return;

	tcb_desc = (struct cb_desc *)(pnewskb->cb + 8);
	tcb_desc->queue_index = BEACON_QUEUE;
	tcb_desc->data_rate = 2;
	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	skb_push(pnewskb, priv->rtllib->tx_headroom);

	pdesc = &ring->desc[0];
	priv->ops->tx_fill_descriptor(dev, pdesc, tcb_desc, pnewskb);
	__skb_queue_tail(&ring->queue, pnewskb);
	pdesc->OWN = 1;
}