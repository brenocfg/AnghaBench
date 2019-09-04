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
struct vb2_queue {int last_buffer_dequeued; int /*<<< orphan*/  done_wq; } ;
struct v4l2_encoder_cmd {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ inst_type; scalar_t__ qsequence; scalar_t__ osequence; TYPE_1__ fh; int /*<<< orphan*/  streamon_out; int /*<<< orphan*/  bit_stream_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_BIT_STREAM_END_FLAG ; 
 scalar_t__ CODA_INST_ENCODER ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int coda_try_encoder_cmd (struct file*,void*,struct v4l2_encoder_cmd*) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 struct vb2_queue* v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coda_encoder_cmd(struct file *file, void *fh,
			    struct v4l2_encoder_cmd *ec)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	struct vb2_queue *dst_vq;
	int ret;

	ret = coda_try_encoder_cmd(file, fh, ec);
	if (ret < 0)
		return ret;

	/* Ignore encoder stop command silently in decoder context */
	if (ctx->inst_type != CODA_INST_ENCODER)
		return 0;

	/* Set the stream-end flag on this context */
	ctx->bit_stream_param |= CODA_BIT_STREAM_END_FLAG;

	/* If there is no buffer in flight, wake up */
	if (!ctx->streamon_out || ctx->qsequence == ctx->osequence) {
		dst_vq = v4l2_m2m_get_vq(ctx->fh.m2m_ctx,
					 V4L2_BUF_TYPE_VIDEO_CAPTURE);
		dst_vq->last_buffer_dequeued = true;
		wake_up(&dst_vq->done_wq);
	}

	return 0;
}