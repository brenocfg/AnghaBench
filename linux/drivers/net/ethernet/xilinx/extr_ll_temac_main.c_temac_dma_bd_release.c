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
struct temac_local {int /*<<< orphan*/  tx_bd_p; TYPE_2__* tx_bd_v; int /*<<< orphan*/  rx_bd_p; TYPE_2__* rx_bd_v; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  (* dma_out ) (struct temac_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CONTROL_REG ; 
 int /*<<< orphan*/  DMA_CONTROL_RST ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int RX_BD_NUM ; 
 int TX_BD_NUM ; 
 int /*<<< orphan*/  XTE_MAX_JUMBO_FRAME_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct temac_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void temac_dma_bd_release(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	int i;

	/* Reset Local Link (DMA) */
	lp->dma_out(lp, DMA_CONTROL_REG, DMA_CONTROL_RST);

	for (i = 0; i < RX_BD_NUM; i++) {
		if (!lp->rx_skb[i])
			break;
		else {
			dma_unmap_single(ndev->dev.parent, lp->rx_bd_v[i].phys,
					XTE_MAX_JUMBO_FRAME_SIZE, DMA_FROM_DEVICE);
			dev_kfree_skb(lp->rx_skb[i]);
		}
	}
	if (lp->rx_bd_v)
		dma_free_coherent(ndev->dev.parent,
				sizeof(*lp->rx_bd_v) * RX_BD_NUM,
				lp->rx_bd_v, lp->rx_bd_p);
	if (lp->tx_bd_v)
		dma_free_coherent(ndev->dev.parent,
				sizeof(*lp->tx_bd_v) * TX_BD_NUM,
				lp->tx_bd_v, lp->tx_bd_p);
}