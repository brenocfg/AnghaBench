#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* m2m_ctx; } ;
struct vicodec_ctx {int has_stopped; int /*<<< orphan*/  lock; TYPE_4__ fh; scalar_t__ is_draining; } ;
struct v4l2_decoder_cmd {scalar_t__ cmd; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  q; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct TYPE_7__ {TYPE_2__ cap_q_ctx; TYPE_1__ out_q_ctx; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ V4L2_DEC_CMD_STOP ; 
 struct vicodec_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int v4l2_m2m_ioctl_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 
 int /*<<< orphan*/  vb2_clear_last_buffer_dequeued (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int vicodec_mark_last_buf (struct vicodec_ctx*) ; 

__attribute__((used)) static int vicodec_decoder_cmd(struct file *file, void *fh,
			    struct v4l2_decoder_cmd *dc)
{
	struct vicodec_ctx *ctx = file2ctx(file);
	int ret;

	ret = v4l2_m2m_ioctl_try_decoder_cmd(file, fh, dc);
	if (ret < 0)
		return ret;

	if (!vb2_is_streaming(&ctx->fh.m2m_ctx->cap_q_ctx.q) ||
	    !vb2_is_streaming(&ctx->fh.m2m_ctx->out_q_ctx.q))
		return 0;

	if (dc->cmd == V4L2_DEC_CMD_STOP)
		return vicodec_mark_last_buf(ctx);
	ret = 0;
	spin_lock(ctx->lock);
	if (ctx->is_draining) {
		ret = -EBUSY;
	} else if (ctx->has_stopped) {
		ctx->has_stopped = false;
		vb2_clear_last_buffer_dequeued(&ctx->fh.m2m_ctx->cap_q_ctx.q);
	}
	spin_unlock(ctx->lock);
	return ret;
}