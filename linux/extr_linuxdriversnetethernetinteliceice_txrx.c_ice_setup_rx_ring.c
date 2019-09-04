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
typedef  union ice_32byte_rx_desc {int dummy; } ice_32byte_rx_desc ;
struct ice_rx_buf {int dummy; } ;
struct ice_ring {int count; int size; int /*<<< orphan*/ * rx_buf; scalar_t__ next_to_clean; scalar_t__ next_to_use; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; struct device* dev; } ;
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

int ice_setup_rx_ring(struct ice_ring *rx_ring)
{
	struct device *dev = rx_ring->dev;
	int bi_size;

	if (!dev)
		return -ENOMEM;

	/* warn if we are about to overwrite the pointer */
	WARN_ON(rx_ring->rx_buf);
	bi_size = sizeof(struct ice_rx_buf) * rx_ring->count;
	rx_ring->rx_buf = devm_kzalloc(dev, bi_size, GFP_KERNEL);
	if (!rx_ring->rx_buf)
		return -ENOMEM;

	/* round up to nearest 4K */
	rx_ring->size = rx_ring->count * sizeof(union ice_32byte_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);
	rx_ring->desc = dmam_alloc_coherent(dev, rx_ring->size, &rx_ring->dma,
					    GFP_KERNEL);
	if (!rx_ring->desc) {
		dev_err(dev, "Unable to allocate memory for the Rx descriptor ring, size=%d\n",
			rx_ring->size);
		goto err;
	}

	rx_ring->next_to_use = 0;
	rx_ring->next_to_clean = 0;
	return 0;

err:
	devm_kfree(dev, rx_ring->rx_buf);
	rx_ring->rx_buf = NULL;
	return -ENOMEM;
}