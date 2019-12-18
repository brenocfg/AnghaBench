#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vicodec_q_data {int /*<<< orphan*/  sequence; } ;
struct TYPE_10__ {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  m2m_dev; } ;
struct vicodec_dev {TYPE_4__ stateful_dec; TYPE_3__ stateless_dec; TYPE_2__ stateful_enc; } ;
struct TYPE_12__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vicodec_ctx {int comp_has_next_frame; int is_draining; int has_stopped; scalar_t__ cur_buf_offset; int comp_has_frame; TYPE_6__ fh; scalar_t__ is_stateless; scalar_t__ is_enc; int /*<<< orphan*/  hdl; int /*<<< orphan*/  lock; scalar_t__ comp_magic_cnt; scalar_t__ header_size; scalar_t__ comp_size; struct vb2_v4l2_buffer* last_src_buf; struct vicodec_dev* dev; } ;
struct TYPE_7__ {struct media_request* req; } ;
struct TYPE_11__ {TYPE_1__ req_obj; } ;
struct vb2_v4l2_buffer {scalar_t__ sequence; TYPE_5__ vb2_buf; int /*<<< orphan*/  flags; } ;
struct media_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 scalar_t__ device_process (struct vicodec_ctx*,struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_complete (struct media_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_copy_metadata (struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*,int) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vicodec_eos_event ; 

__attribute__((used)) static void device_run(void *priv)
{
	struct vicodec_ctx *ctx = priv;
	struct vicodec_dev *dev = ctx->dev;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	struct vicodec_q_data *q_src, *q_dst;
	u32 state;
	struct media_request *src_req;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	src_req = src_buf->vb2_buf.req_obj.req;

	q_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
	q_dst = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);

	state = VB2_BUF_STATE_DONE;
	if (device_process(ctx, src_buf, dst_buf))
		state = VB2_BUF_STATE_ERROR;
	else
		dst_buf->sequence = q_dst->sequence++;
	dst_buf->flags &= ~V4L2_BUF_FLAG_LAST;
	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);

	spin_lock(ctx->lock);
	if (!ctx->comp_has_next_frame && src_buf == ctx->last_src_buf) {
		dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		v4l2_event_queue_fh(&ctx->fh, &vicodec_eos_event);
		ctx->is_draining = false;
		ctx->has_stopped = true;
	}
	if (ctx->is_enc || ctx->is_stateless) {
		src_buf->sequence = q_src->sequence++;
		src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_done(src_buf, state);
	} else if (vb2_get_plane_payload(&src_buf->vb2_buf, 0) == ctx->cur_buf_offset) {
		src_buf->sequence = q_src->sequence++;
		src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		v4l2_m2m_buf_done(src_buf, state);
		ctx->cur_buf_offset = 0;
		ctx->comp_has_next_frame = false;
	}
	v4l2_m2m_buf_done(dst_buf, state);

	ctx->comp_size = 0;
	ctx->header_size = 0;
	ctx->comp_magic_cnt = 0;
	ctx->comp_has_frame = false;
	spin_unlock(ctx->lock);
	if (ctx->is_stateless && src_req)
		v4l2_ctrl_request_complete(src_req, &ctx->hdl);

	if (ctx->is_enc)
		v4l2_m2m_job_finish(dev->stateful_enc.m2m_dev, ctx->fh.m2m_ctx);
	else if (ctx->is_stateless)
		v4l2_m2m_job_finish(dev->stateless_dec.m2m_dev,
				    ctx->fh.m2m_ctx);
	else
		v4l2_m2m_job_finish(dev->stateful_dec.m2m_dev, ctx->fh.m2m_ctx);
}