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
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct can_frame {int /*<<< orphan*/  can_dlc; } ;
struct c_can_priv {int /*<<< orphan*/  tx_active; int /*<<< orphan*/ * dlc; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int C_CAN_MSG_OBJ_TX_FIRST ; 
 int C_CAN_MSG_OBJ_TX_NUM ; 
 int /*<<< orphan*/  IF_COMM_TX ; 
 int /*<<< orphan*/  IF_TX ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_can_object_put (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_can_setup_tx_object (struct net_device*,int /*<<< orphan*/ ,struct can_frame*,int) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 int fls (int /*<<< orphan*/ ) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t c_can_start_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	struct can_frame *frame = (struct can_frame *)skb->data;
	struct c_can_priv *priv = netdev_priv(dev);
	u32 idx, obj;

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;
	/*
	 * This is not a FIFO. C/D_CAN sends out the buffers
	 * prioritized. The lowest buffer number wins.
	 */
	idx = fls(atomic_read(&priv->tx_active));
	obj = idx + C_CAN_MSG_OBJ_TX_FIRST;

	/* If this is the last buffer, stop the xmit queue */
	if (idx == C_CAN_MSG_OBJ_TX_NUM - 1)
		netif_stop_queue(dev);
	/*
	 * Store the message in the interface so we can call
	 * can_put_echo_skb(). We must do this before we enable
	 * transmit as we might race against do_tx().
	 */
	c_can_setup_tx_object(dev, IF_TX, frame, idx);
	priv->dlc[idx] = frame->can_dlc;
	can_put_echo_skb(skb, dev, idx);

	/* Update the active bits */
	atomic_add((1 << idx), &priv->tx_active);
	/* Start transmission */
	c_can_object_put(dev, IF_TX, obj, IF_COMM_TX);

	return NETDEV_TX_OK;
}