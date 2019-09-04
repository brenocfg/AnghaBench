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
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; int /*<<< orphan*/  timecode; TYPE_1__ vb2_buf; } ;
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; TYPE_3__* gsc_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_dev; } ;
struct TYPE_6__ {TYPE_2__ m2m; } ;

/* Variables and functions */
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

void gsc_m2m_job_finish(struct gsc_ctx *ctx, int vb_state)
{
	struct vb2_v4l2_buffer *src_vb, *dst_vb;

	if (!ctx || !ctx->m2m_ctx)
		return;

	src_vb = v4l2_m2m_src_buf_remove(ctx->m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(ctx->m2m_ctx);

	if (src_vb && dst_vb) {
		dst_vb->vb2_buf.timestamp = src_vb->vb2_buf.timestamp;
		dst_vb->timecode = src_vb->timecode;
		dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst_vb->flags |=
			src_vb->flags
			& V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_done(src_vb, vb_state);
		v4l2_m2m_buf_done(dst_vb, vb_state);

		v4l2_m2m_job_finish(ctx->gsc_dev->m2m.m2m_dev,
				    ctx->m2m_ctx);
	}
}