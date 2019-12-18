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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct axienet_local {int rx_bd_num; int tx_bd_num; int /*<<< orphan*/  tx_bd_p; TYPE_2__* tx_bd_v; int /*<<< orphan*/  rx_bd_p; TYPE_2__* rx_bd_v; int /*<<< orphan*/  max_frm_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  skb; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void axienet_dma_bd_release(struct net_device *ndev)
{
	int i;
	struct axienet_local *lp = netdev_priv(ndev);

	for (i = 0; i < lp->rx_bd_num; i++) {
		dma_unmap_single(ndev->dev.parent, lp->rx_bd_v[i].phys,
				 lp->max_frm_size, DMA_FROM_DEVICE);
		dev_kfree_skb(lp->rx_bd_v[i].skb);
	}

	if (lp->rx_bd_v) {
		dma_free_coherent(ndev->dev.parent,
				  sizeof(*lp->rx_bd_v) * lp->rx_bd_num,
				  lp->rx_bd_v,
				  lp->rx_bd_p);
	}
	if (lp->tx_bd_v) {
		dma_free_coherent(ndev->dev.parent,
				  sizeof(*lp->tx_bd_v) * lp->tx_bd_num,
				  lp->tx_bd_v,
				  lp->tx_bd_p);
	}
}