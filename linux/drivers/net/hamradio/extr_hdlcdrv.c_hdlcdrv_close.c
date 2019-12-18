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
struct net_device {int dummy; } ;
struct hdlcdrv_state {scalar_t__ opened; int /*<<< orphan*/ * skb; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* close ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 struct hdlcdrv_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int stub1 (struct net_device*) ; 

__attribute__((used)) static int hdlcdrv_close(struct net_device *dev)
{
	struct hdlcdrv_state *s = netdev_priv(dev);
	int i = 0;

	netif_stop_queue(dev);

	if (s->ops && s->ops->close)
		i = s->ops->close(dev);
	dev_kfree_skb(s->skb);
	s->skb = NULL;
	s->opened = 0;
	return i;
}