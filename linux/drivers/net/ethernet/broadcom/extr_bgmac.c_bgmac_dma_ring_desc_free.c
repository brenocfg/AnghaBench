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
struct device {int dummy; } ;
struct bgmac_dma_ring {int /*<<< orphan*/  dma_base; int /*<<< orphan*/  cpu_base; } ;
struct bgmac_dma_desc {int dummy; } ;
struct bgmac {struct device* dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgmac_dma_ring_desc_free(struct bgmac *bgmac,
				     struct bgmac_dma_ring *ring,
				     int num_slots)
{
	struct device *dma_dev = bgmac->dma_dev;
	int size;

	if (!ring->cpu_base)
	    return;

	/* Free ring of descriptors */
	size = num_slots * sizeof(struct bgmac_dma_desc);
	dma_free_coherent(dma_dev, size, ring->cpu_base,
			  ring->dma_base);
}