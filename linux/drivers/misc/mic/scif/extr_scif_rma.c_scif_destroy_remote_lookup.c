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
struct scif_rma_lookup {int /*<<< orphan*/  offset; scalar_t__* lookup; } ;
struct scif_window {int nr_lookup; int nr_pages; scalar_t__ mapped_offset; struct scif_rma_lookup num_pages_lookup; struct scif_rma_lookup dma_addr_lookup; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ SCIF_NR_ADDR_IN_PAGE ; 
 int /*<<< orphan*/  scif_free_coherent (scalar_t__*,int /*<<< orphan*/ ,struct scif_dev*,int) ; 
 int /*<<< orphan*/  scif_unmap_single (scalar_t__,struct scif_dev*,int) ; 

__attribute__((used)) static void scif_destroy_remote_lookup(struct scif_dev *remote_dev,
				       struct scif_window *window)
{
	int i, j;

	if (window->nr_lookup) {
		struct scif_rma_lookup *lup = &window->dma_addr_lookup;
		struct scif_rma_lookup *npup = &window->num_pages_lookup;

		for (i = 0, j = 0; i < window->nr_pages;
			i += SCIF_NR_ADDR_IN_PAGE, j++) {
			if (lup->lookup && lup->lookup[j])
				scif_unmap_single(lup->lookup[j],
						  remote_dev,
						  PAGE_SIZE);
			if (npup->lookup && npup->lookup[j])
				scif_unmap_single(npup->lookup[j],
						  remote_dev,
						  PAGE_SIZE);
		}
		if (lup->lookup)
			scif_free_coherent(lup->lookup, lup->offset,
					   remote_dev, window->nr_lookup *
					   sizeof(*lup->lookup));
		if (npup->lookup)
			scif_free_coherent(npup->lookup, npup->offset,
					   remote_dev, window->nr_lookup *
					   sizeof(*npup->lookup));
		if (window->mapped_offset)
			scif_unmap_single(window->mapped_offset,
					  remote_dev, sizeof(*window));
		window->nr_lookup = 0;
	}
}