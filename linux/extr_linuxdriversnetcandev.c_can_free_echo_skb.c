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
struct net_device {int dummy; } ;
struct can_priv {unsigned int echo_skb_max; int /*<<< orphan*/ ** echo_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

void can_free_echo_skb(struct net_device *dev, unsigned int idx)
{
	struct can_priv *priv = netdev_priv(dev);

	BUG_ON(idx >= priv->echo_skb_max);

	if (priv->echo_skb[idx]) {
		dev_kfree_skb_any(priv->echo_skb[idx]);
		priv->echo_skb[idx] = NULL;
	}
}