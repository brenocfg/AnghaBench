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
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  restarts; } ;
struct can_priv {int (* do_set_mode ) (struct net_device*,int /*<<< orphan*/ ) ;TYPE_1__ can_stats; } ;
struct can_frame {scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAN_ERR_RESTARTED ; 
 int /*<<< orphan*/  CAN_MODE_START ; 
 int ENOMEM ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_flush_echo_skb (struct net_device*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void can_restart(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct sk_buff *skb;
	struct can_frame *cf;
	int err;

	BUG_ON(netif_carrier_ok(dev));

	/* No synchronization needed because the device is bus-off and
	 * no messages can come in or go out.
	 */
	can_flush_echo_skb(dev);

	/* send restart message upstream */
	skb = alloc_can_err_skb(dev, &cf);
	if (!skb) {
		err = -ENOMEM;
		goto restart;
	}
	cf->can_id |= CAN_ERR_RESTARTED;

	netif_rx(skb);

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;

restart:
	netdev_dbg(dev, "restarted\n");
	priv->can_stats.restarts++;

	/* Now restart the device */
	err = priv->do_set_mode(dev, CAN_MODE_START);

	netif_carrier_on(dev);
	if (err)
		netdev_err(dev, "Error %d during restart", err);
}