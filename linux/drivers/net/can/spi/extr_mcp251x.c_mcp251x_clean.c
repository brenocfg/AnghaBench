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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct mcp251x_priv {scalar_t__ tx_len; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_free_echo_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mcp251x_clean(struct net_device *net)
{
	struct mcp251x_priv *priv = netdev_priv(net);

	if (priv->tx_skb || priv->tx_len)
		net->stats.tx_errors++;
	dev_kfree_skb(priv->tx_skb);
	if (priv->tx_len)
		can_free_echo_skb(priv->net, 0);
	priv->tx_skb = NULL;
	priv->tx_len = 0;
}