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
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* command ) (struct net_device*,int) ;int /*<<< orphan*/  (* status ) (struct net_device*) ;} ;
struct arcnet_local {int intmask; int next_tx; int cur_tx; scalar_t__ excnak_pending; scalar_t__ lastload_dest; scalar_t__ lasttrans_dest; TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ BUGLVL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_DURING ; 
 int /*<<< orphan*/  D_TX ; 
 int EXCNAKflag ; 
 int TXFREEflag ; 
 int TXcmd ; 
 int /*<<< orphan*/  arc_printk (int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  arcnet_dump_packet (struct net_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int) ; 

__attribute__((used)) static int go_tx(struct net_device *dev)
{
	struct arcnet_local *lp = netdev_priv(dev);

	arc_printk(D_DURING, dev, "go_tx: status=%Xh, intmask=%Xh, next_tx=%d, cur_tx=%d\n",
		   lp->hw.status(dev), lp->intmask, lp->next_tx, lp->cur_tx);

	if (lp->cur_tx != -1 || lp->next_tx == -1)
		return 0;

	if (BUGLVL(D_TX))
		arcnet_dump_packet(dev, lp->next_tx, "go_tx", 0);

	lp->cur_tx = lp->next_tx;
	lp->next_tx = -1;

	/* start sending */
	lp->hw.command(dev, TXcmd | (lp->cur_tx << 3));

	dev->stats.tx_packets++;
	lp->lasttrans_dest = lp->lastload_dest;
	lp->lastload_dest = 0;
	lp->excnak_pending = 0;
	lp->intmask |= TXFREEflag | EXCNAKflag;

	return 1;
}