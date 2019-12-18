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
struct sxgbe_tx_queue {int /*<<< orphan*/  dma_tx_phy; int /*<<< orphan*/  dma_tx; } ;
struct sxgbe_tx_norm_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_tx_ring(struct device *dev, struct sxgbe_tx_queue *tx_ring,
			 int tx_rsize)
{
	dma_free_coherent(dev, tx_rsize * sizeof(struct sxgbe_tx_norm_desc),
			  tx_ring->dma_tx, tx_ring->dma_tx_phy);
}