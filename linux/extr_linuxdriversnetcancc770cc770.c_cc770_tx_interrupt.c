#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_over_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct cc770_priv {TYPE_2__* tx_skb; } ;
struct can_frame {scalar_t__ can_dlc; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl1; int /*<<< orphan*/  ctrl0; } ;

/* Variables and functions */
 int INTPND_RES ; 
 int MSGLST_RES ; 
 int MSGLST_SET ; 
 int MSGVAL_RES ; 
 int NEWDAT_RES ; 
 int NEWDAT_SET ; 
 int RMTPND_RES ; 
 int RXIE_RES ; 
 int TXIE_RES ; 
 int TXRQST_RES ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_put_echo_skb (TYPE_2__*,struct net_device*,int /*<<< orphan*/ ) ; 
 int cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_rx (struct net_device*,unsigned int,int) ; 
 int /*<<< orphan*/  cc770_tx (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  cc770_write_reg (struct cc770_priv*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* msgobj ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 unsigned int obj2msgobj (unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cc770_tx_interrupt(struct net_device *dev, unsigned int o)
{
	struct cc770_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	unsigned int mo = obj2msgobj(o);
	struct can_frame *cf;
	u8 ctrl1;

	ctrl1 = cc770_read_reg(priv, msgobj[mo].ctrl1);

	cc770_write_reg(priv, msgobj[mo].ctrl0,
			MSGVAL_RES | TXIE_RES | RXIE_RES | INTPND_RES);
	cc770_write_reg(priv, msgobj[mo].ctrl1,
			RMTPND_RES | TXRQST_RES | MSGLST_RES | NEWDAT_RES);

	if (unlikely(!priv->tx_skb)) {
		netdev_err(dev, "missing tx skb in tx interrupt\n");
		return;
	}

	if (unlikely(ctrl1 & MSGLST_SET)) {
		stats->rx_over_errors++;
		stats->rx_errors++;
	}

	/* When the CC770 is sending an RTR message and it receives a regular
	 * message that matches the id of the RTR message, it will overwrite the
	 * outgoing message in the TX register. When this happens we must
	 * process the received message and try to transmit the outgoing skb
	 * again.
	 */
	if (unlikely(ctrl1 & NEWDAT_SET)) {
		cc770_rx(dev, mo, ctrl1);
		cc770_tx(dev, mo);
		return;
	}

	cf = (struct can_frame *)priv->tx_skb->data;
	stats->tx_bytes += cf->can_dlc;
	stats->tx_packets++;

	can_put_echo_skb(priv->tx_skb, dev, 0);
	can_get_echo_skb(dev, 0);
	priv->tx_skb = NULL;

	netif_wake_queue(dev);
}