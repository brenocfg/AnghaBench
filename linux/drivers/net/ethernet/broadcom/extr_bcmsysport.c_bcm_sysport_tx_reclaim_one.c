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
struct device {int dummy; } ;
struct bcm_sysport_tx_ring {struct bcm_sysport_priv* priv; } ;
struct bcm_sysport_priv {TYPE_2__* pdev; } ;
struct bcm_sysport_cb {TYPE_1__* skb; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  bcm_sysport_free_cb (struct bcm_sysport_cb*) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 scalar_t__ dma_unmap_addr (struct bcm_sysport_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bcm_sysport_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct bcm_sysport_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_tx_reclaim_one(struct bcm_sysport_tx_ring *ring,
				       struct bcm_sysport_cb *cb,
				       unsigned int *bytes_compl,
				       unsigned int *pkts_compl)
{
	struct bcm_sysport_priv *priv = ring->priv;
	struct device *kdev = &priv->pdev->dev;

	if (cb->skb) {
		*bytes_compl += cb->skb->len;
		dma_unmap_single(kdev, dma_unmap_addr(cb, dma_addr),
				 dma_unmap_len(cb, dma_len),
				 DMA_TO_DEVICE);
		(*pkts_compl)++;
		bcm_sysport_free_cb(cb);
	/* SKB fragment */
	} else if (dma_unmap_addr(cb, dma_addr)) {
		*bytes_compl += dma_unmap_len(cb, dma_len);
		dma_unmap_page(kdev, dma_unmap_addr(cb, dma_addr),
			       dma_unmap_len(cb, dma_len), DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	}
}