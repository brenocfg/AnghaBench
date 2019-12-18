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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct de4x5_private {TYPE_1__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
de4x5_put_cache(struct net_device *dev, struct sk_buff *skb)
{
    struct de4x5_private *lp = netdev_priv(dev);

    __skb_queue_tail(&lp->cache.queue, skb);
}