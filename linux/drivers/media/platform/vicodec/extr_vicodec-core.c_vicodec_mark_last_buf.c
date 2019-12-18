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
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int is_draining; int has_stopped; int next_is_last; int /*<<< orphan*/  lock; TYPE_1__ fh; scalar_t__ last_src_buf; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_m2m_last_src_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vicodec_eos_event ; 

__attribute__((used)) static int vicodec_mark_last_buf(struct vicodec_ctx *ctx)
{
	struct vb2_v4l2_buffer *next_dst_buf;
	int ret = 0;

	spin_lock(ctx->lock);
	if (ctx->is_draining) {
		ret = -EBUSY;
		goto unlock;
	}
	if (ctx->has_stopped)
		goto unlock;

	ctx->last_src_buf = v4l2_m2m_last_src_buf(ctx->fh.m2m_ctx);
	ctx->is_draining = true;
	if (ctx->last_src_buf)
		goto unlock;

	next_dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	if (!next_dst_buf) {
		ctx->next_is_last = true;
		goto unlock;
	}

	next_dst_buf->flags |= V4L2_BUF_FLAG_LAST;
	vb2_buffer_done(&next_dst_buf->vb2_buf, VB2_BUF_STATE_DONE);
	ctx->is_draining = false;
	ctx->has_stopped = true;
	v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);

unlock:
	spin_unlock(ctx->lock);
	return ret;
}