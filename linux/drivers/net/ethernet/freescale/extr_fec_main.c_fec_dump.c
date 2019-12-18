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
struct net_device {int dummy; } ;
struct fec_enet_private {struct fec_enet_priv_tx_q** tx_queue; } ;
struct TYPE_2__ {struct bufdesc* cur; struct bufdesc* base; } ;
struct fec_enet_priv_tx_q {TYPE_1__ bd; int /*<<< orphan*/ * tx_skbuff; struct bufdesc* dirty_tx; } ;
struct bufdesc {int /*<<< orphan*/  cbd_datlen; int /*<<< orphan*/  cbd_bufaddr; int /*<<< orphan*/  cbd_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fec16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec32_to_cpu (int /*<<< orphan*/ ) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static void fec_dump(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc *bdp;
	struct fec_enet_priv_tx_q *txq;
	int index = 0;

	netdev_info(ndev, "TX ring dump\n");
	pr_info("Nr     SC     addr       len  SKB\n");

	txq = fep->tx_queue[0];
	bdp = txq->bd.base;

	do {
		pr_info("%3u %c%c 0x%04x 0x%08x %4u %p\n",
			index,
			bdp == txq->bd.cur ? 'S' : ' ',
			bdp == txq->dirty_tx ? 'H' : ' ',
			fec16_to_cpu(bdp->cbd_sc),
			fec32_to_cpu(bdp->cbd_bufaddr),
			fec16_to_cpu(bdp->cbd_datlen),
			txq->tx_skbuff[index]);
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		index++;
	} while (bdp != txq->bd.base);
}