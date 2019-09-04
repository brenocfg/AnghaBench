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
struct videobuf_queue {int /*<<< orphan*/  dev; } ;
struct videobuf_dma_contig_memory {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  magic; } ;
struct videobuf_buffer {scalar_t__ memory; scalar_t__ baddr; struct videobuf_dma_contig_memory* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_DC_MEM ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  __videobuf_dc_free (int /*<<< orphan*/ ,struct videobuf_dma_contig_memory*) ; 
 int /*<<< orphan*/  videobuf_dma_contig_user_put (struct videobuf_dma_contig_memory*) ; 

void videobuf_dma_contig_free(struct videobuf_queue *q,
			      struct videobuf_buffer *buf)
{
	struct videobuf_dma_contig_memory *mem = buf->priv;

	/* mmapped memory can't be freed here, otherwise mmapped region
	   would be released, while still needed. In this case, the memory
	   release should happen inside videobuf_vm_close().
	   So, it should free memory only if the memory were allocated for
	   read() operation.
	 */
	if (buf->memory != V4L2_MEMORY_USERPTR)
		return;

	if (!mem)
		return;

	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	/* handle user space pointer case */
	if (buf->baddr) {
		videobuf_dma_contig_user_put(mem);
		return;
	}

	/* read() method */
	if (mem->vaddr) {
		__videobuf_dc_free(q->dev, mem);
		mem->vaddr = NULL;
	}
}