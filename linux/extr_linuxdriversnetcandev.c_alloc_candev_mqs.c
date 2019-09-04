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
struct net_device {int dummy; } ;
struct can_priv {unsigned int echo_skb_max; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  state; void* echo_skb; struct net_device* dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev_mqs (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  can_restart_work ; 
 int /*<<< orphan*/  can_setup ; 
 struct can_priv* netdev_priv (struct net_device*) ; 

struct net_device *alloc_candev_mqs(int sizeof_priv, unsigned int echo_skb_max,
				    unsigned int txqs, unsigned int rxqs)
{
	struct net_device *dev;
	struct can_priv *priv;
	int size;

	if (echo_skb_max)
		size = ALIGN(sizeof_priv, sizeof(struct sk_buff *)) +
			echo_skb_max * sizeof(struct sk_buff *);
	else
		size = sizeof_priv;

	dev = alloc_netdev_mqs(size, "can%d", NET_NAME_UNKNOWN, can_setup,
			       txqs, rxqs);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);
	priv->dev = dev;

	if (echo_skb_max) {
		priv->echo_skb_max = echo_skb_max;
		priv->echo_skb = (void *)priv +
			ALIGN(sizeof_priv, sizeof(struct sk_buff *));
	}

	priv->state = CAN_STATE_STOPPED;

	INIT_DELAYED_WORK(&priv->restart_work, can_restart_work);

	return dev;
}