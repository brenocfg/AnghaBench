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
typedef  int u32 ;
struct dma_desc {int dummy; } ;
struct device {int dummy; } ;
struct bcm_sysport_tx_ring {scalar_t__ alloc_size; scalar_t__ size; scalar_t__ desc_dma; int /*<<< orphan*/  desc_cpu; int /*<<< orphan*/ * cbs; int /*<<< orphan*/  napi; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct bcm_sysport_tx_ring* tx_rings; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int TDMA_DISABLED ; 
 int /*<<< orphan*/  TDMA_STATUS ; 
 int /*<<< orphan*/  bcm_sysport_tx_clean (struct bcm_sysport_priv*,struct bcm_sysport_tx_ring*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int tdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_fini_tx_ring(struct bcm_sysport_priv *priv,
				     unsigned int index)
{
	struct bcm_sysport_tx_ring *ring = &priv->tx_rings[index];
	struct device *kdev = &priv->pdev->dev;
	u32 reg;

	/* Caller should stop the TDMA engine */
	reg = tdma_readl(priv, TDMA_STATUS);
	if (!(reg & TDMA_DISABLED))
		netdev_warn(priv->netdev, "TDMA not stopped!\n");

	/* ring->cbs is the last part in bcm_sysport_init_tx_ring which could
	 * fail, so by checking this pointer we know whether the TX ring was
	 * fully initialized or not.
	 */
	if (!ring->cbs)
		return;

	napi_disable(&ring->napi);
	netif_napi_del(&ring->napi);

	bcm_sysport_tx_clean(priv, ring);

	kfree(ring->cbs);
	ring->cbs = NULL;

	if (ring->desc_dma) {
		dma_free_coherent(kdev, sizeof(struct dma_desc),
				  ring->desc_cpu, ring->desc_dma);
		ring->desc_dma = 0;
	}
	ring->size = 0;
	ring->alloc_size = 0;

	netif_dbg(priv, hw, priv->netdev, "TDMA fini done\n");
}