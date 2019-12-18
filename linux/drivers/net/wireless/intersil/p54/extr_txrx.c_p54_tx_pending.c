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
struct p54_common {int /*<<< orphan*/  hw; int /*<<< orphan*/  (* tx ) (int /*<<< orphan*/ ,struct sk_buff*) ;int /*<<< orphan*/  tx_pending; } ;

/* Variables and functions */
 int p54_assign_address (struct p54_common*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void p54_tx_pending(struct p54_common *priv)
{
	struct sk_buff *skb;
	int ret;

	skb = skb_dequeue(&priv->tx_pending);
	if (unlikely(!skb))
		return ;

	ret = p54_assign_address(priv, skb);
	if (unlikely(ret))
		skb_queue_head(&priv->tx_pending, skb);
	else
		priv->tx(priv->hw, skb);
}