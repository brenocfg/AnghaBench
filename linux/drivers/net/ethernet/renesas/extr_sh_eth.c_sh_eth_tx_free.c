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
struct sh_eth_txdesc {int status; int addr; int len; } ;
struct sh_eth_private {scalar_t__ cur_tx; int dirty_tx; int num_tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_1__* pdev; struct sh_eth_txdesc* tx_ring; } ;
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  TD_TACT ; 
 int /*<<< orphan*/  TD_TDLE ; 
 int /*<<< orphan*/  TD_TFP ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct sh_eth_private*,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  tx_done ; 

__attribute__((used)) static int sh_eth_tx_free(struct net_device *ndev, bool sent_only)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	struct sh_eth_txdesc *txdesc;
	int free_num = 0;
	int entry;
	bool sent;

	for (; mdp->cur_tx - mdp->dirty_tx > 0; mdp->dirty_tx++) {
		entry = mdp->dirty_tx % mdp->num_tx_ring;
		txdesc = &mdp->tx_ring[entry];
		sent = !(txdesc->status & cpu_to_le32(TD_TACT));
		if (sent_only && !sent)
			break;
		/* TACT bit must be checked before all the following reads */
		dma_rmb();
		netif_info(mdp, tx_done, ndev,
			   "tx entry %d status 0x%08x\n",
			   entry, le32_to_cpu(txdesc->status));
		/* Free the original skb. */
		if (mdp->tx_skbuff[entry]) {
			dma_unmap_single(&mdp->pdev->dev,
					 le32_to_cpu(txdesc->addr),
					 le32_to_cpu(txdesc->len) >> 16,
					 DMA_TO_DEVICE);
			dev_kfree_skb_irq(mdp->tx_skbuff[entry]);
			mdp->tx_skbuff[entry] = NULL;
			free_num++;
		}
		txdesc->status = cpu_to_le32(TD_TFP);
		if (entry >= mdp->num_tx_ring - 1)
			txdesc->status |= cpu_to_le32(TD_TDLE);

		if (sent) {
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += le32_to_cpu(txdesc->len) >> 16;
		}
	}
	return free_num;
}