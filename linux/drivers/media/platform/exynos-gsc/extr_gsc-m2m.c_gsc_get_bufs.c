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
struct TYPE_2__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {TYPE_1__ vb2_buf; } ;
struct gsc_frame {int /*<<< orphan*/  addr; } ;
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; struct gsc_frame d_frame; struct gsc_frame s_frame; } ;

/* Variables and functions */
 int gsc_prepare_addr (struct gsc_ctx*,TYPE_1__*,struct gsc_frame*,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsc_get_bufs(struct gsc_ctx *ctx)
{
	struct gsc_frame *s_frame, *d_frame;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	int ret;

	s_frame = &ctx->s_frame;
	d_frame = &ctx->d_frame;

	src_vb = v4l2_m2m_next_src_buf(ctx->m2m_ctx);
	ret = gsc_prepare_addr(ctx, &src_vb->vb2_buf, s_frame, &s_frame->addr);
	if (ret)
		return ret;

	dst_vb = v4l2_m2m_next_dst_buf(ctx->m2m_ctx);
	ret = gsc_prepare_addr(ctx, &dst_vb->vb2_buf, d_frame, &d_frame->addr);
	if (ret)
		return ret;

	dst_vb->vb2_buf.timestamp = src_vb->vb2_buf.timestamp;

	return 0;
}