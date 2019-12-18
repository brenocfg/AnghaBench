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
struct vb2_dma_sg_buf {int dummy; } ;
struct dma_buf {struct vb2_dma_sg_buf* priv; } ;

/* Variables and functions */
 void* vb2_dma_sg_vaddr (struct vb2_dma_sg_buf*) ; 

__attribute__((used)) static void *vb2_dma_sg_dmabuf_ops_vmap(struct dma_buf *dbuf)
{
	struct vb2_dma_sg_buf *buf = dbuf->priv;

	return vb2_dma_sg_vaddr(buf);
}