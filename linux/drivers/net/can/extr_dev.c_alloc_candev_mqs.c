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
struct net_device {void* ml_priv; } ;
struct can_priv {unsigned int echo_skb_max; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  state; void* echo_skb; struct net_device* dev; } ;
struct can_ml_priv {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETDEV_ALIGN ; 
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

	/* We put the driver's priv, the CAN mid layer priv and the
	 * echo skb into the netdevice's priv. The memory layout for
	 * the netdev_priv is like this:
	 *
	 * +-------------------------+
	 * | driver's priv           |
	 * +-------------------------+
	 * | struct can_ml_priv      |
	 * +-------------------------+
	 * | array of struct sk_buff |
	 * +-------------------------+
	 */

	size = ALIGN(sizeof_priv, NETDEV_ALIGN) + sizeof(struct can_ml_priv);

	if (echo_skb_max)
		size = ALIGN(size, sizeof(struct sk_buff *)) +
			echo_skb_max * sizeof(struct sk_buff *);

	dev = alloc_netdev_mqs(size, "can%d", NET_NAME_UNKNOWN, can_setup,
			       txqs, rxqs);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);
	priv->dev = dev;

	dev->ml_priv = (void *)priv + ALIGN(sizeof_priv, NETDEV_ALIGN);

	if (echo_skb_max) {
		priv->echo_skb_max = echo_skb_max;
		priv->echo_skb = (void *)priv +
			(size - echo_skb_max * sizeof(struct sk_buff *));
	}

	priv->state = CAN_STATE_STOPPED;

	INIT_DELAYED_WORK(&priv->restart_work, can_restart_work);

	return dev;
}