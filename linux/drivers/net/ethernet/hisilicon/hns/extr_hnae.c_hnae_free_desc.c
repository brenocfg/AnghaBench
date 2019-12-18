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
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_to_dev (struct hnae_ring*) ; 
 int /*<<< orphan*/  ring_to_dma_dir (struct hnae_ring*) ; 

__attribute__((used)) static void hnae_free_desc(struct hnae_ring *ring)
{
	dma_unmap_single(ring_to_dev(ring), ring->desc_dma_addr,
			 ring->desc_num * sizeof(ring->desc[0]),
			 ring_to_dma_dir(ring));
	ring->desc_dma_addr = 0;
	kfree(ring->desc);
	ring->desc = NULL;
}