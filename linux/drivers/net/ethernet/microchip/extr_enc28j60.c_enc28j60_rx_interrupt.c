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
struct net_device {int dummy; } ;
struct enc28j60_net {int max_pk_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPKTCNT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  enc28j60_hw_rx (struct net_device*) ; 
 int locked_regb_read (struct enc28j60_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_intr (struct enc28j60_net*) ; 
 scalar_t__ netif_msg_rx_status (struct enc28j60_net*) ; 

__attribute__((used)) static int enc28j60_rx_interrupt(struct net_device *ndev)
{
	struct enc28j60_net *priv = netdev_priv(ndev);
	int pk_counter, ret;

	pk_counter = locked_regb_read(priv, EPKTCNT);
	if (pk_counter && netif_msg_intr(priv))
		netdev_printk(KERN_DEBUG, ndev, "intRX, pk_cnt: %d\n",
			      pk_counter);
	if (pk_counter > priv->max_pk_counter) {
		/* update statistics */
		priv->max_pk_counter = pk_counter;
		if (netif_msg_rx_status(priv) && priv->max_pk_counter > 1)
			netdev_printk(KERN_DEBUG, ndev, "RX max_pk_cnt: %d\n",
				      priv->max_pk_counter);
	}
	ret = pk_counter;
	while (pk_counter-- > 0)
		enc28j60_hw_rx(ndev);

	return ret;
}