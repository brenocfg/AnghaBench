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
struct sh_eth_txdesc {int dummy; } ;
struct sh_eth_rxdesc {int dummy; } ;
struct sh_eth_private {int rx_buf_sz; int num_rx_ring; int num_tx_ring; void* tx_ring; int /*<<< orphan*/  tx_desc_dma; TYPE_2__* pdev; scalar_t__ dirty_rx; void* rx_ring; int /*<<< orphan*/  rx_desc_dma; void* tx_skbuff; void* rx_skbuff; TYPE_1__* cd; } ;
struct net_device {int mtu; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ rpadir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NET_IP_ALIGN ; 
 int PKT_BUF_SZ ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_ring_free (struct net_device*) ; 

__attribute__((used)) static int sh_eth_ring_init(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int rx_ringsize, tx_ringsize;

	/* +26 gets the maximum ethernet encapsulation, +7 & ~7 because the
	 * card needs room to do 8 byte alignment, +2 so we can reserve
	 * the first 2 bytes, and +16 gets room for the status word from the
	 * card.
	 */
	mdp->rx_buf_sz = (ndev->mtu <= 1492 ? PKT_BUF_SZ :
			  (((ndev->mtu + 26 + 7) & ~7) + 2 + 16));
	if (mdp->cd->rpadir)
		mdp->rx_buf_sz += NET_IP_ALIGN;

	/* Allocate RX and TX skb rings */
	mdp->rx_skbuff = kcalloc(mdp->num_rx_ring, sizeof(*mdp->rx_skbuff),
				 GFP_KERNEL);
	if (!mdp->rx_skbuff)
		return -ENOMEM;

	mdp->tx_skbuff = kcalloc(mdp->num_tx_ring, sizeof(*mdp->tx_skbuff),
				 GFP_KERNEL);
	if (!mdp->tx_skbuff)
		goto ring_free;

	/* Allocate all Rx descriptors. */
	rx_ringsize = sizeof(struct sh_eth_rxdesc) * mdp->num_rx_ring;
	mdp->rx_ring = dma_alloc_coherent(&mdp->pdev->dev, rx_ringsize,
					  &mdp->rx_desc_dma, GFP_KERNEL);
	if (!mdp->rx_ring)
		goto ring_free;

	mdp->dirty_rx = 0;

	/* Allocate all Tx descriptors. */
	tx_ringsize = sizeof(struct sh_eth_txdesc) * mdp->num_tx_ring;
	mdp->tx_ring = dma_alloc_coherent(&mdp->pdev->dev, tx_ringsize,
					  &mdp->tx_desc_dma, GFP_KERNEL);
	if (!mdp->tx_ring)
		goto ring_free;
	return 0;

ring_free:
	/* Free Rx and Tx skb ring buffer and DMA buffer */
	sh_eth_ring_free(ndev);

	return -ENOMEM;
}