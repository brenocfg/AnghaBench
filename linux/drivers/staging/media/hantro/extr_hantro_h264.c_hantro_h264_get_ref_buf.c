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
struct vb2_buffer {int dummy; } ;
struct vb2_v4l2_buffer {struct vb2_buffer vb2_buf; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_h264_dpb_entry {int flags; int /*<<< orphan*/  reference_ts; } ;
struct TYPE_8__ {struct v4l2_h264_dpb_entry* dpb; } ;
struct TYPE_7__ {TYPE_2__* m2m_ctx; } ;
struct hantro_ctx {TYPE_4__ h264_dec; TYPE_3__ fh; } ;
struct TYPE_5__ {struct vb2_queue q; } ;
struct TYPE_6__ {TYPE_1__ cap_q_ctx; } ;

/* Variables and functions */
 int V4L2_H264_DPB_ENTRY_FLAG_ACTIVE ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 int vb2_find_timestamp (struct vb2_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_buffer* vb2_get_buffer (struct vb2_queue*,int) ; 

struct vb2_buffer *hantro_h264_get_ref_buf(struct hantro_ctx *ctx,
					   unsigned int dpb_idx)
{
	struct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	struct v4l2_h264_dpb_entry *dpb = ctx->h264_dec.dpb;
	struct vb2_buffer *buf;
	int buf_idx = -1;

	if (dpb[dpb_idx].flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE)
		buf_idx = vb2_find_timestamp(cap_q,
					     dpb[dpb_idx].reference_ts, 0);

	if (buf_idx >= 0) {
		buf = vb2_get_buffer(cap_q, buf_idx);
	} else {
		struct vb2_v4l2_buffer *dst_buf;

		/*
		 * If a DPB entry is unused or invalid, address of current
		 * destination buffer is returned.
		 */
		dst_buf = hantro_get_dst_buf(ctx);
		buf = &dst_buf->vb2_buf;
	}

	return buf;
}