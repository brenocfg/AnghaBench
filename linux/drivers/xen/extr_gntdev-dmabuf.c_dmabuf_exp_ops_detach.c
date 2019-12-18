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
struct sg_table {int /*<<< orphan*/  dir; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; struct sg_table* sgt; } ;
struct gntdev_dmabuf_attachment {int /*<<< orphan*/  dir; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; struct gntdev_dmabuf_attachment* sgt; } ;
struct dma_buf_attachment {struct sg_table* priv; int /*<<< orphan*/  dev; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  dma_unmap_sg_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 

__attribute__((used)) static void dmabuf_exp_ops_detach(struct dma_buf *dma_buf,
				  struct dma_buf_attachment *attach)
{
	struct gntdev_dmabuf_attachment *gntdev_dmabuf_attach = attach->priv;

	if (gntdev_dmabuf_attach) {
		struct sg_table *sgt = gntdev_dmabuf_attach->sgt;

		if (sgt) {
			if (gntdev_dmabuf_attach->dir != DMA_NONE)
				dma_unmap_sg_attrs(attach->dev, sgt->sgl,
						   sgt->nents,
						   gntdev_dmabuf_attach->dir,
						   DMA_ATTR_SKIP_CPU_SYNC);
			sg_free_table(sgt);
		}

		kfree(sgt);
		kfree(gntdev_dmabuf_attach);
		attach->priv = NULL;
	}
}