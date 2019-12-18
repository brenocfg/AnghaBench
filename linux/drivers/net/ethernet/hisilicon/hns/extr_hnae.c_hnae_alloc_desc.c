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
struct hnae_ring {int desc_num; int /*<<< orphan*/ * desc; scalar_t__ desc_dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_to_dev (struct hnae_ring*) ; 
 int /*<<< orphan*/  ring_to_dma_dir (struct hnae_ring*) ; 

__attribute__((used)) static int hnae_alloc_desc(struct hnae_ring *ring)
{
	int size = ring->desc_num * sizeof(ring->desc[0]);

	ring->desc = kzalloc(size, GFP_KERNEL);
	if (!ring->desc)
		return -ENOMEM;

	ring->desc_dma_addr = dma_map_single(ring_to_dev(ring),
		ring->desc, size, ring_to_dma_dir(ring));
	if (dma_mapping_error(ring_to_dev(ring), ring->desc_dma_addr)) {
		ring->desc_dma_addr = 0;
		kfree(ring->desc);
		ring->desc = NULL;
		return -ENOMEM;
	}

	return 0;
}