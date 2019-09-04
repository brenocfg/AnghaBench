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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int state; } ;
struct rcar_canfd_channel {TYPE_1__ can; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {scalar_t__ can_dlc; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_change_state (struct net_device*,struct can_frame*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int,int,int) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void rcar_canfd_state_change(struct net_device *ndev,
				    u16 txerr, u16 rxerr)
{
	struct rcar_canfd_channel *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	enum can_state rx_state, tx_state, state = priv->can.state;
	struct can_frame *cf;
	struct sk_buff *skb;

	/* Handle transition from error to normal states */
	if (txerr < 96 && rxerr < 96)
		state = CAN_STATE_ERROR_ACTIVE;
	else if (txerr < 128 && rxerr < 128)
		state = CAN_STATE_ERROR_WARNING;

	if (state != priv->can.state) {
		netdev_dbg(ndev, "state: new %d, old %d: txerr %u, rxerr %u\n",
			   state, priv->can.state, txerr, rxerr);
		skb = alloc_can_err_skb(ndev, &cf);
		if (!skb) {
			stats->rx_dropped++;
			return;
		}
		tx_state = txerr >= rxerr ? state : 0;
		rx_state = txerr <= rxerr ? state : 0;

		can_change_state(ndev, cf, tx_state, rx_state);
		stats->rx_packets++;
		stats->rx_bytes += cf->can_dlc;
		netif_rx(skb);
	}
}