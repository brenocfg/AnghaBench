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
struct scif_dma_comp_cb {int /*<<< orphan*/  temp_buf_to_free; scalar_t__ is_cache; int /*<<< orphan*/  sdev; int /*<<< orphan*/  temp_phys; int /*<<< orphan*/  len; scalar_t__ header_padding; scalar_t__ temp_buf; scalar_t__ dst_window; int /*<<< orphan*/  dst_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_KMEM_UNALIGNED_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_rma_local_cpu_copy (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scif_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unaligned_cache ; 

__attribute__((used)) static void scif_rma_completion_cb(void *data)
{
	struct scif_dma_comp_cb *comp_cb = data;

	/* Free DMA Completion CB. */
	if (comp_cb->dst_window)
		scif_rma_local_cpu_copy(comp_cb->dst_offset,
					comp_cb->dst_window,
					comp_cb->temp_buf +
					comp_cb->header_padding,
					comp_cb->len, false);
	scif_unmap_single(comp_cb->temp_phys, comp_cb->sdev,
			  SCIF_KMEM_UNALIGNED_BUF_SIZE);
	if (comp_cb->is_cache)
		kmem_cache_free(unaligned_cache,
				comp_cb->temp_buf_to_free);
	else
		kfree(comp_cb->temp_buf_to_free);
}