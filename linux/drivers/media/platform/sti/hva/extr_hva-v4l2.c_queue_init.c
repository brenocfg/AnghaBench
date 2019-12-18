#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int io_modes; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct hva_ctx* drv_priv; } ;
struct hva_ctx {TYPE_1__* hva_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_COPY ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int /*<<< orphan*/  hva_qops ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 

__attribute__((used)) static int queue_init(struct hva_ctx *ctx, struct vb2_queue *vq)
{
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->drv_priv = ctx;
	vq->ops = &hva_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	vq->lock = &ctx->hva_dev->lock;

	return vb2_queue_init(vq);
}