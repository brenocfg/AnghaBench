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
struct vb2_dc_buf {int /*<<< orphan*/  vec; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; struct vb2_dc_buf* dma_sgt; } ;
struct sg_table {int /*<<< orphan*/  vec; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; struct sg_table* dma_sgt; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IS_ERR (struct page**) ; 
 int /*<<< orphan*/  dma_unmap_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int frame_vector_count (int /*<<< orphan*/ ) ; 
 struct page** frame_vector_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vb2_dc_buf*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  sg_free_table (struct vb2_dc_buf*) ; 
 int /*<<< orphan*/  vb2_destroy_framevec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vb2_dc_put_userptr(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;
	struct sg_table *sgt = buf->dma_sgt;
	int i;
	struct page **pages;

	if (sgt) {
		/*
		 * No need to sync to CPU, it's already synced to the CPU
		 * since the finish() memop will have been called before this.
		 */
		dma_unmap_sg_attrs(buf->dev, sgt->sgl, sgt->orig_nents,
				   buf->dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
		pages = frame_vector_pages(buf->vec);
		/* sgt should exist only if vector contains pages... */
		BUG_ON(IS_ERR(pages));
		if (buf->dma_dir == DMA_FROM_DEVICE ||
		    buf->dma_dir == DMA_BIDIRECTIONAL)
			for (i = 0; i < frame_vector_count(buf->vec); i++)
				set_page_dirty_lock(pages[i]);
		sg_free_table(sgt);
		kfree(sgt);
	} else {
		dma_unmap_resource(buf->dev, buf->dma_addr, buf->size,
				   buf->dma_dir, 0);
	}
	vb2_destroy_framevec(buf->vec);
	kfree(buf);
}