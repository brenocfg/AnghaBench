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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct greth_private {int tx_last; scalar_t__ tx_free; scalar_t__* tx_bufs_length; TYPE_1__* regs; struct greth_bd* tx_bd_base; } ;
struct greth_bd {int /*<<< orphan*/  stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int GRETH_BD_EN ; 
 int GRETH_INT_TE ; 
 int GRETH_INT_TX ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int GRETH_TXBD_ERR_AL ; 
 int GRETH_TXBD_ERR_UE ; 
 scalar_t__ GRETH_TXBD_NUM ; 
 int GRETH_TXBD_STATUS ; 
 size_t NEXT_TX (size_t) ; 
 int greth_read_bd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void greth_clean_tx(struct net_device *dev)
{
	struct greth_private *greth;
	struct greth_bd *bdp;
	u32 stat;

	greth = netdev_priv(dev);

	while (1) {
		bdp = greth->tx_bd_base + greth->tx_last;
		GRETH_REGSAVE(greth->regs->status, GRETH_INT_TE | GRETH_INT_TX);
		mb();
		stat = greth_read_bd(&bdp->stat);

		if (unlikely(stat & GRETH_BD_EN))
			break;

		if (greth->tx_free == GRETH_TXBD_NUM)
			break;

		/* Check status for errors */
		if (unlikely(stat & GRETH_TXBD_STATUS)) {
			dev->stats.tx_errors++;
			if (stat & GRETH_TXBD_ERR_AL)
				dev->stats.tx_aborted_errors++;
			if (stat & GRETH_TXBD_ERR_UE)
				dev->stats.tx_fifo_errors++;
		}
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += greth->tx_bufs_length[greth->tx_last];
		greth->tx_last = NEXT_TX(greth->tx_last);
		greth->tx_free++;
	}

	if (greth->tx_free > 0) {
		netif_wake_queue(dev);
	}
}