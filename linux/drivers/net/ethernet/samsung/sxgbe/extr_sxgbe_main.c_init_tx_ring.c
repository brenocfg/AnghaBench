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
typedef  int /*<<< orphan*/  u8 ;
struct sxgbe_tx_queue {int /*<<< orphan*/  dma_tx_phy; int /*<<< orphan*/  dma_tx; scalar_t__ cur_tx; scalar_t__ dirty_tx; int /*<<< orphan*/  queue_no; void* tx_skbuff; void* tx_skbuff_dma; } ;
struct sxgbe_tx_norm_desc {int dummy; } ;
struct sk_buff {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_tx_ring(struct device *dev, u8 queue_no,
			struct sxgbe_tx_queue *tx_ring,	int tx_rsize)
{
	/* TX ring is not allcoated */
	if (!tx_ring) {
		dev_err(dev, "No memory for TX queue of SXGBE\n");
		return -ENOMEM;
	}

	/* allocate memory for TX descriptors */
	tx_ring->dma_tx = dma_alloc_coherent(dev,
					     tx_rsize * sizeof(struct sxgbe_tx_norm_desc),
					     &tx_ring->dma_tx_phy, GFP_KERNEL);
	if (!tx_ring->dma_tx)
		return -ENOMEM;

	/* allocate memory for TX skbuff array */
	tx_ring->tx_skbuff_dma = devm_kcalloc(dev, tx_rsize,
					      sizeof(dma_addr_t), GFP_KERNEL);
	if (!tx_ring->tx_skbuff_dma)
		goto dmamem_err;

	tx_ring->tx_skbuff = devm_kcalloc(dev, tx_rsize,
					  sizeof(struct sk_buff *), GFP_KERNEL);

	if (!tx_ring->tx_skbuff)
		goto dmamem_err;

	/* assign queue number */
	tx_ring->queue_no = queue_no;

	/* initialise counters */
	tx_ring->dirty_tx = 0;
	tx_ring->cur_tx = 0;

	return 0;

dmamem_err:
	dma_free_coherent(dev, tx_rsize * sizeof(struct sxgbe_tx_norm_desc),
			  tx_ring->dma_tx, tx_ring->dma_tx_phy);
	return -ENOMEM;
}