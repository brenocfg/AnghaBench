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
struct vb2_v4l2_buffer {int /*<<< orphan*/  flags; } ;
struct v4l2_encoder_cmd {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {int /*<<< orphan*/  wakeup_mutex; int /*<<< orphan*/  bit_stream_param; TYPE_1__ fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_BIT_STREAM_END_FLAG ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 int coda_try_encoder_cmd (struct file*,void*,struct v4l2_encoder_cmd*) ; 
 int /*<<< orphan*/  coda_wake_up_capture_queue (struct coda_ctx*) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_last_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_encoder_cmd(struct file *file, void *fh,
			    struct v4l2_encoder_cmd *ec)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	struct vb2_v4l2_buffer *buf;
	int ret;

	ret = coda_try_encoder_cmd(file, fh, ec);
	if (ret < 0)
		return ret;

	mutex_lock(&ctx->wakeup_mutex);
	buf = v4l2_m2m_last_src_buf(ctx->fh.m2m_ctx);
	if (buf) {
		/*
		 * If the last output buffer is still on the queue, make sure
		 * that decoder finish_run will see the last flag and report it
		 * to userspace.
		 */
		buf->flags |= V4L2_BUF_FLAG_LAST;
	} else {
		/* Set the stream-end flag on this context */
		ctx->bit_stream_param |= CODA_BIT_STREAM_END_FLAG;

		/*
		 * If the last output buffer has already been taken from the
		 * queue, wake up the capture queue and signal end of stream
		 * via the -EPIPE mechanism.
		 */
		coda_wake_up_capture_queue(ctx);
	}
	mutex_unlock(&ctx->wakeup_mutex);

	return 0;
}