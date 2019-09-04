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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb_task; int /*<<< orphan*/  skb_queue; } ;
struct ipoib_dev_priv {TYPE_1__ cm; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_update_pmtu (struct sk_buff*,unsigned int) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void ipoib_cm_skb_too_long(struct net_device *dev, struct sk_buff *skb,
			   unsigned int mtu)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int e = skb_queue_empty(&priv->cm.skb_queue);

	skb_dst_update_pmtu(skb, mtu);

	skb_queue_tail(&priv->cm.skb_queue, skb);
	if (e)
		queue_work(priv->wq, &priv->cm.skb_task);
}