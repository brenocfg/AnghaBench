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
struct ice_tx_desc {int dummy; } ;
struct ice_tx_buf {int dummy; } ;
struct ice_ring {int count; int size; int /*<<< orphan*/ * tx_buf; scalar_t__ next_to_clean; scalar_t__ next_to_use; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ice_setup_tx_ring(struct ice_ring *tx_ring)
{
	struct device *dev = tx_ring->dev;
	int bi_size;

	if (!dev)
		return -ENOMEM;

	/* warn if we are about to overwrite the pointer */
	WARN_ON(tx_ring->tx_buf);
	bi_size = sizeof(struct ice_tx_buf) * tx_ring->count;
	tx_ring->tx_buf = devm_kzalloc(dev, bi_size, GFP_KERNEL);
	if (!tx_ring->tx_buf)
		return -ENOMEM;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * sizeof(struct ice_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);
	tx_ring->desc = dmam_alloc_coherent(dev, tx_ring->size, &tx_ring->dma,
					    GFP_KERNEL);
	if (!tx_ring->desc) {
		dev_err(dev, "Unable to allocate memory for the Tx descriptor ring, size=%d\n",
			tx_ring->size);
		goto err;
	}

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	return 0;

err:
	devm_kfree(dev, tx_ring->tx_buf);
	tx_ring->tx_buf = NULL;
	return -ENOMEM;
}