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
struct vb2_dc_buf {int /*<<< orphan*/  refcount; scalar_t__ sgt_base; int /*<<< orphan*/  size; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {unsigned long flags; struct vb2_dc_buf* priv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_1__) ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct dma_buf* dma_buf_export (TYPE_1__*) ; 
 TYPE_1__ exp_info ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dc_dmabuf_ops ; 
 scalar_t__ vb2_dc_get_base_sgt (struct vb2_dc_buf*) ; 

__attribute__((used)) static struct dma_buf *vb2_dc_get_dmabuf(void *buf_priv, unsigned long flags)
{
	struct vb2_dc_buf *buf = buf_priv;
	struct dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_dc_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	if (!buf->sgt_base)
		buf->sgt_base = vb2_dc_get_base_sgt(buf);

	if (WARN_ON(!buf->sgt_base))
		return NULL;

	dbuf = dma_buf_export(&exp_info);
	if (IS_ERR(dbuf))
		return NULL;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	return dbuf;
}