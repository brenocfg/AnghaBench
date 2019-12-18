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
struct gntdev_dmabuf_attachment {int /*<<< orphan*/  dir; } ;
struct dma_buf_attachment {struct gntdev_dmabuf_attachment* priv; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gntdev_dmabuf_attachment* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmabuf_exp_ops_attach(struct dma_buf *dma_buf,
				 struct dma_buf_attachment *attach)
{
	struct gntdev_dmabuf_attachment *gntdev_dmabuf_attach;

	gntdev_dmabuf_attach = kzalloc(sizeof(*gntdev_dmabuf_attach),
				       GFP_KERNEL);
	if (!gntdev_dmabuf_attach)
		return -ENOMEM;

	gntdev_dmabuf_attach->dir = DMA_NONE;
	attach->priv = gntdev_dmabuf_attach;
	return 0;
}