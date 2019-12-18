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
struct ethoc_bd {int stat; } ;
struct ethoc {int dty_tx; int num_tx; int cur_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_TX ; 
 int TX_BD_READY ; 
 int /*<<< orphan*/  ethoc_ack_irq (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_read_bd (struct ethoc*,unsigned int,struct ethoc_bd*) ; 
 int /*<<< orphan*/  ethoc_update_tx_stats (struct ethoc*,struct ethoc_bd*) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static int ethoc_tx(struct net_device *dev, int limit)
{
	struct ethoc *priv = netdev_priv(dev);
	int count;
	struct ethoc_bd bd;

	for (count = 0; count < limit; ++count) {
		unsigned int entry;

		entry = priv->dty_tx & (priv->num_tx-1);

		ethoc_read_bd(priv, entry, &bd);

		if (bd.stat & TX_BD_READY || (priv->dty_tx == priv->cur_tx)) {
			ethoc_ack_irq(priv, INT_MASK_TX);
			/* If interrupt came in between reading in the BD
			 * and clearing the interrupt source, then we risk
			 * missing the event as the TX interrupt won't trigger
			 * right away when we reenable it; hence, check
			 * BD_EMPTY here again to make sure there isn't such an
			 * event pending...
			 */
			ethoc_read_bd(priv, entry, &bd);
			if (bd.stat & TX_BD_READY ||
			    (priv->dty_tx == priv->cur_tx))
				break;
		}

		ethoc_update_tx_stats(priv, &bd);
		priv->dty_tx++;
	}

	if ((priv->cur_tx - priv->dty_tx) <= (priv->num_tx / 2))
		netif_wake_queue(dev);

	return count;
}