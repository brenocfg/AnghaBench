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
struct hnae_desc_cb {int /*<<< orphan*/  dma; int /*<<< orphan*/  length; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_to_dev (struct hnae_ring*) ; 
 int /*<<< orphan*/  ring_to_dma_dir (struct hnae_ring*) ; 

__attribute__((used)) static int hnae_map_buffer(struct hnae_ring *ring, struct hnae_desc_cb *cb)
{
	cb->dma = dma_map_page(ring_to_dev(ring), cb->priv, 0,
			       cb->length, ring_to_dma_dir(ring));

	if (dma_mapping_error(ring_to_dev(ring), cb->dma))
		return -EIO;

	return 0;
}