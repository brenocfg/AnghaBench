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
struct sh_eth_txdesc {int dummy; } ;
struct sh_eth_rxdesc {int /*<<< orphan*/  addr; } ;
struct sh_eth_private {int num_rx_ring; int num_tx_ring; scalar_t__* tx_skbuff; struct sh_eth_rxdesc* tx_ring; int /*<<< orphan*/  tx_desc_dma; TYPE_1__* pdev; scalar_t__* rx_skbuff; struct sh_eth_rxdesc* rx_ring; int /*<<< orphan*/  rx_desc_dma; int /*<<< orphan*/  rx_buf_sz; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct sh_eth_rxdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_tx_free (struct net_device*,int) ; 

__attribute__((used)) static void sh_eth_ring_free(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int ringsize, i;

	if (mdp->rx_ring) {
		for (i = 0; i < mdp->num_rx_ring; i++) {
			if (mdp->rx_skbuff[i]) {
				struct sh_eth_rxdesc *rxdesc = &mdp->rx_ring[i];

				dma_unmap_single(&mdp->pdev->dev,
						 le32_to_cpu(rxdesc->addr),
						 ALIGN(mdp->rx_buf_sz, 32),
						 DMA_FROM_DEVICE);
			}
		}
		ringsize = sizeof(struct sh_eth_rxdesc) * mdp->num_rx_ring;
		dma_free_coherent(&mdp->pdev->dev, ringsize, mdp->rx_ring,
				  mdp->rx_desc_dma);
		mdp->rx_ring = NULL;
	}

	/* Free Rx skb ringbuffer */
	if (mdp->rx_skbuff) {
		for (i = 0; i < mdp->num_rx_ring; i++)
			dev_kfree_skb(mdp->rx_skbuff[i]);
	}
	kfree(mdp->rx_skbuff);
	mdp->rx_skbuff = NULL;

	if (mdp->tx_ring) {
		sh_eth_tx_free(ndev, false);

		ringsize = sizeof(struct sh_eth_txdesc) * mdp->num_tx_ring;
		dma_free_coherent(&mdp->pdev->dev, ringsize, mdp->tx_ring,
				  mdp->tx_desc_dma);
		mdp->tx_ring = NULL;
	}

	/* Free Tx skb ringbuffer */
	kfree(mdp->tx_skbuff);
	mdp->tx_skbuff = NULL;
}