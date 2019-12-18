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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_phys; } ;
struct hisi_femac_priv {int /*<<< orphan*/  dev; TYPE_1__ txq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_femac_tx_dma_unmap(struct hisi_femac_priv *priv,
				    struct sk_buff *skb, unsigned int pos)
{
	dma_addr_t dma_addr;

	dma_addr = priv->txq.dma_phys[pos];
	dma_unmap_single(priv->dev, dma_addr, skb->len, DMA_TO_DEVICE);
}