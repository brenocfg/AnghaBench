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
struct tx_queue {int /*<<< orphan*/  tx_ring_size; } ;
struct net_device {int dummy; } ;
struct mv643xx_eth_private {int txq_count; struct tx_queue* txq; struct net_device* dev; } ;

/* Variables and functions */
 int FLOW_CONTROL_ENABLED ; 
 int FULL_DUPLEX ; 
 int LINK_UP ; 
#define  PORT_SPEED_10 130 
#define  PORT_SPEED_100 129 
#define  PORT_SPEED_1000 128 
 int PORT_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_STATUS ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txq_reclaim (struct tx_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txq_reset_hw_ptr (struct tx_queue*) ; 

__attribute__((used)) static void handle_link_event(struct mv643xx_eth_private *mp)
{
	struct net_device *dev = mp->dev;
	u32 port_status;
	int speed;
	int duplex;
	int fc;

	port_status = rdlp(mp, PORT_STATUS);
	if (!(port_status & LINK_UP)) {
		if (netif_carrier_ok(dev)) {
			int i;

			netdev_info(dev, "link down\n");

			netif_carrier_off(dev);

			for (i = 0; i < mp->txq_count; i++) {
				struct tx_queue *txq = mp->txq + i;

				txq_reclaim(txq, txq->tx_ring_size, 1);
				txq_reset_hw_ptr(txq);
			}
		}
		return;
	}

	switch (port_status & PORT_SPEED_MASK) {
	case PORT_SPEED_10:
		speed = 10;
		break;
	case PORT_SPEED_100:
		speed = 100;
		break;
	case PORT_SPEED_1000:
		speed = 1000;
		break;
	default:
		speed = -1;
		break;
	}
	duplex = (port_status & FULL_DUPLEX) ? 1 : 0;
	fc = (port_status & FLOW_CONTROL_ENABLED) ? 1 : 0;

	netdev_info(dev, "link up, %d Mb/s, %s duplex, flow control %sabled\n",
		    speed, duplex ? "full" : "half", fc ? "en" : "dis");

	if (!netif_carrier_ok(dev))
		netif_carrier_on(dev);
}