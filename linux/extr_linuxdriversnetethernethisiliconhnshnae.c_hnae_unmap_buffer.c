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
struct hnae_ring {int dummy; } ;
struct hnae_desc_cb {scalar_t__ type; scalar_t__ length; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 scalar_t__ DESC_TYPE_SKB ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_to_dev (struct hnae_ring*) ; 
 int /*<<< orphan*/  ring_to_dma_dir (struct hnae_ring*) ; 

__attribute__((used)) static void hnae_unmap_buffer(struct hnae_ring *ring, struct hnae_desc_cb *cb)
{
	if (cb->type == DESC_TYPE_SKB)
		dma_unmap_single(ring_to_dev(ring), cb->dma, cb->length,
				 ring_to_dma_dir(ring));
	else if (cb->length)
		dma_unmap_page(ring_to_dev(ring), cb->dma, cb->length,
			       ring_to_dma_dir(ring));
}