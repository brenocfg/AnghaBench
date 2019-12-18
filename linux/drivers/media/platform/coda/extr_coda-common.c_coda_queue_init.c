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
struct vb2_queue {int buf_struct_size; int allow_zero_bytesused; int min_buffers_needed; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * ops; struct coda_ctx* drv_priv; } ;
struct v4l2_m2m_buffer {int dummy; } ;
struct coda_ctx {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_COPY ; 
 int /*<<< orphan*/  coda_qops ; 
 int vb2_queue_init (struct vb2_queue*) ; 

__attribute__((used)) static int coda_queue_init(struct coda_ctx *ctx, struct vb2_queue *vq)
{
	vq->drv_priv = ctx;
	vq->ops = &coda_qops;
	vq->buf_struct_size = sizeof(struct v4l2_m2m_buffer);
	vq->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	vq->lock = &ctx->dev->dev_mutex;
	/* One way to indicate end-of-stream for coda is to set the
	 * bytesused == 0. However by default videobuf2 handles bytesused
	 * equal to 0 as a special case and changes its value to the size
	 * of the buffer. Set the allow_zero_bytesused flag, so
	 * that videobuf2 will keep the value of bytesused intact.
	 */
	vq->allow_zero_bytesused = 1;
	/*
	 * We might be fine with no buffers on some of the queues, but that
	 * would need to be reflected in job_ready(). Currently we expect all
	 * queues to have at least one buffer queued.
	 */
	vq->min_buffers_needed = 1;
	vq->dev = ctx->dev->dev;

	return vb2_queue_init(vq);
}