#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int tx_bytes; int collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_3__ stats; } ;
struct ep93xx_tstat {int tstat0; } ;
struct ep93xx_priv {int tx_clean_pointer; int tx_pending; int /*<<< orphan*/  tx_pending_lock; TYPE_2__* descs; } ;
struct TYPE_5__ {TYPE_1__* tdesc; struct ep93xx_tstat* tstat; } ;
struct TYPE_4__ {int tdesc1; } ;

/* Variables and functions */
 int TSTAT0_BUFFER_INDEX ; 
 int TSTAT0_FA ; 
 int TSTAT0_OW ; 
 int TSTAT0_TXFP ; 
 int TSTAT0_TXU ; 
 int TSTAT0_TXWE ; 
 int TX_QUEUE_ENTRIES ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_crit (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep93xx_tx_complete(struct net_device *dev)
{
	struct ep93xx_priv *ep = netdev_priv(dev);
	int wake;

	wake = 0;

	spin_lock(&ep->tx_pending_lock);
	while (1) {
		int entry;
		struct ep93xx_tstat *tstat;
		u32 tstat0;

		entry = ep->tx_clean_pointer;
		tstat = ep->descs->tstat + entry;

		tstat0 = tstat->tstat0;
		if (!(tstat0 & TSTAT0_TXFP))
			break;

		tstat->tstat0 = 0;

		if (tstat0 & TSTAT0_FA)
			pr_crit("frame aborted %.8x\n", tstat0);
		if ((tstat0 & TSTAT0_BUFFER_INDEX) != entry)
			pr_crit("entry mismatch %.8x\n", tstat0);

		if (tstat0 & TSTAT0_TXWE) {
			int length = ep->descs->tdesc[entry].tdesc1 & 0xfff;

			dev->stats.tx_packets++;
			dev->stats.tx_bytes += length;
		} else {
			dev->stats.tx_errors++;
		}

		if (tstat0 & TSTAT0_OW)
			dev->stats.tx_window_errors++;
		if (tstat0 & TSTAT0_TXU)
			dev->stats.tx_fifo_errors++;
		dev->stats.collisions += (tstat0 >> 16) & 0x1f;

		ep->tx_clean_pointer = (entry + 1) & (TX_QUEUE_ENTRIES - 1);
		if (ep->tx_pending == TX_QUEUE_ENTRIES)
			wake = 1;
		ep->tx_pending--;
	}
	spin_unlock(&ep->tx_pending_lock);

	if (wake)
		netif_wake_queue(dev);
}