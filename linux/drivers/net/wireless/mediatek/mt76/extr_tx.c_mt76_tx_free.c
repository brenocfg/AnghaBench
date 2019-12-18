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
struct mt76_txwi_cache {int /*<<< orphan*/  dma_addr; } ;
struct mt76_dev {TYPE_1__* drv; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  txwi_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct mt76_txwi_cache* __mt76_get_txwi (struct mt76_dev*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76_tx_free(struct mt76_dev *dev)
{
	struct mt76_txwi_cache *t;

	while ((t = __mt76_get_txwi(dev)) != NULL)
		dma_unmap_single(dev->dev, t->dma_addr, dev->drv->txwi_size,
				 DMA_TO_DEVICE);
}