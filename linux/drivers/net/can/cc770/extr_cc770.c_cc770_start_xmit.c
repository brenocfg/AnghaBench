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
struct cc770_priv {struct sk_buff* tx_skb; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC770_OBJ_TX ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TXRQST_SET ; 
 int TXRQST_UNC ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_tx (struct net_device*,unsigned int) ; 
 TYPE_1__* msgobj ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 unsigned int obj2msgobj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t cc770_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);
	unsigned int mo = obj2msgobj(CC770_OBJ_TX);

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	netif_stop_queue(dev);

	if ((cc770_read_reg(priv,
			    msgobj[mo].ctrl1) & TXRQST_UNC) == TXRQST_SET) {
		netdev_err(dev, "TX register is still occupied!\n");
		return NETDEV_TX_BUSY;
	}

	priv->tx_skb = skb;
	cc770_tx(dev, mo);

	return NETDEV_TX_OK;
}