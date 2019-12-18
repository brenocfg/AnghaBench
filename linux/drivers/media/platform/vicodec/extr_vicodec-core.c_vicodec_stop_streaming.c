#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * luma; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {TYPE_1__ ref_frame; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int is_draining; int next_is_last; int has_stopped; int first_source_change_sent; int source_changed; scalar_t__ comp_has_next_frame; scalar_t__ comp_has_frame; scalar_t__ comp_magic_cnt; scalar_t__ header_size; scalar_t__ comp_size; scalar_t__ cur_buf_offset; scalar_t__ is_enc; scalar_t__ comp_max_size; TYPE_2__ state; int /*<<< orphan*/  is_stateless; int /*<<< orphan*/  lock; TYPE_3__ fh; int /*<<< orphan*/ * last_src_buf; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; int /*<<< orphan*/  flags; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vicodec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vicodec_eos_event ; 
 int /*<<< orphan*/  vicodec_return_bufs (struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vicodec_stop_streaming(struct vb2_queue *q)
{
	struct vicodec_ctx *ctx = vb2_get_drv_priv(q);

	vicodec_return_bufs(q, VB2_BUF_STATE_ERROR);

	if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		if (ctx->is_draining) {
			struct vb2_v4l2_buffer *next_dst_buf;

			spin_lock(ctx->lock);
			ctx->last_src_buf = NULL;
			next_dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
			if (!next_dst_buf) {
				ctx->next_is_last = true;
			} else {
				next_dst_buf->flags |= V4L2_BUF_FLAG_LAST;
				vb2_buffer_done(&next_dst_buf->vb2_buf, VB2_BUF_STATE_DONE);
				ctx->is_draining = false;
				ctx->has_stopped = true;
				v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);
			}
			spin_unlock(ctx->lock);
		}
	} else {
		ctx->is_draining = false;
		ctx->has_stopped = false;
		ctx->next_is_last = false;
	}
	if (!ctx->is_enc && V4L2_TYPE_IS_OUTPUT(q->type))
		ctx->first_source_change_sent = false;

	if ((!V4L2_TYPE_IS_OUTPUT(q->type) && !ctx->is_enc) ||
	    (V4L2_TYPE_IS_OUTPUT(q->type) && ctx->is_enc)) {
		if (!ctx->is_stateless)
			kvfree(ctx->state.ref_frame.buf);
		ctx->state.ref_frame.buf = NULL;
		ctx->state.ref_frame.luma = NULL;
		ctx->comp_max_size = 0;
		ctx->source_changed = false;
	}
	if (V4L2_TYPE_IS_OUTPUT(q->type) && !ctx->is_enc) {
		ctx->cur_buf_offset = 0;
		ctx->comp_size = 0;
		ctx->header_size = 0;
		ctx->comp_magic_cnt = 0;
		ctx->comp_has_frame = 0;
		ctx->comp_has_next_frame = 0;
	}
}