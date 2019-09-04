#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_dma_sg_buf {int /*<<< orphan*/  refcount; int /*<<< orphan*/  dma_sgt; int /*<<< orphan*/  size; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {unsigned long flags; struct vb2_dma_sg_buf* priv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_1__) ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct dma_buf* dma_buf_export (TYPE_1__*) ; 
 TYPE_1__ exp_info ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_sg_dmabuf_ops ; 

__attribute__((used)) static struct dma_buf *vb2_dma_sg_get_dmabuf(void *buf_priv, unsigned long flags)
{
	struct vb2_dma_sg_buf *buf = buf_priv;
	struct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_dma_sg_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	if (WARN_ON(!buf->dma_sgt))
		return NULL;

	dbuf = dma_buf_export(&exp_info);
	if (IS_ERR(dbuf))
		return NULL;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	return dbuf;
}