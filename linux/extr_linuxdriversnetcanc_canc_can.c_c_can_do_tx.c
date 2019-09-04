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
typedef  int u32 ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct c_can_priv {int (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;int* dlc; int /*<<< orphan*/  tx_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int /*<<< orphan*/  C_CAN_INTPND2_REG ; 
 int C_CAN_MSG_OBJ_TX_FIRST ; 
 int C_CAN_MSG_OBJ_TX_NUM ; 
 int /*<<< orphan*/  IF_RX ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_can_inval_tx_object (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c_can_do_tx(struct net_device *dev)
{
	struct c_can_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	u32 idx, obj, pkts = 0, bytes = 0, pend, clr;

	clr = pend = priv->read_reg(priv, C_CAN_INTPND2_REG);

	while ((idx = ffs(pend))) {
		idx--;
		pend &= ~(1 << idx);
		obj = idx + C_CAN_MSG_OBJ_TX_FIRST;
		c_can_inval_tx_object(dev, IF_RX, obj);
		can_get_echo_skb(dev, idx);
		bytes += priv->dlc[idx];
		pkts++;
	}

	/* Clear the bits in the tx_active mask */
	atomic_sub(clr, &priv->tx_active);

	if (clr & (1 << (C_CAN_MSG_OBJ_TX_NUM - 1)))
		netif_wake_queue(dev);

	if (pkts) {
		stats->tx_bytes += bytes;
		stats->tx_packets += pkts;
		can_led_event(dev, CAN_LED_EVENT_TX);
	}
}