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
typedef  union fm10k_rx_desc {int dummy; } fm10k_rx_desc ;
struct fm10k_rx_buffer {int dummy; } ;
struct fm10k_ring {int count; int size; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  syncp; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

int fm10k_setup_rx_resources(struct fm10k_ring *rx_ring)
{
	struct device *dev = rx_ring->dev;
	int size;

	size = sizeof(struct fm10k_rx_buffer) * rx_ring->count;

	rx_ring->rx_buffer = vzalloc(size);
	if (!rx_ring->rx_buffer)
		goto err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * sizeof(union fm10k_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	if (!rx_ring->desc)
		goto err;

	return 0;
err:
	vfree(rx_ring->rx_buffer);
	rx_ring->rx_buffer = NULL;
	return -ENOMEM;
}