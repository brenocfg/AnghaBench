#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct altera_tse_private {int /*<<< orphan*/  txdescmem; scalar_t__ txdescphys; int /*<<< orphan*/  device; int /*<<< orphan*/  rxdescmem; scalar_t__ rxdescphys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sgdma_uninitialize(struct altera_tse_private *priv)
{
	if (priv->rxdescphys)
		dma_unmap_single(priv->device, priv->rxdescphys,
				 priv->rxdescmem, DMA_BIDIRECTIONAL);

	if (priv->txdescphys)
		dma_unmap_single(priv->device, priv->txdescphys,
				 priv->txdescmem, DMA_TO_DEVICE);
}