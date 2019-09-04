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
struct sk_buff {int dummy; } ;
struct enet_cb {int dummy; } ;
struct bcmgenet_priv {int num_rx_bds; TYPE_1__* pdev; struct enet_cb* rx_cbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sk_buff* bcmgenet_free_rx_cb (int /*<<< orphan*/ *,struct enet_cb*) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 

__attribute__((used)) static void bcmgenet_free_rx_buffers(struct bcmgenet_priv *priv)
{
	struct sk_buff *skb;
	struct enet_cb *cb;
	int i;

	for (i = 0; i < priv->num_rx_bds; i++) {
		cb = &priv->rx_cbs[i];

		skb = bcmgenet_free_rx_cb(&priv->pdev->dev, cb);
		if (skb)
			dev_consume_skb_any(skb);
	}
}