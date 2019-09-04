#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;
struct bdisp_frame {int /*<<< orphan*/  paddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct bdisp_ctx {TYPE_1__ fh; struct bdisp_frame dst; struct bdisp_frame src; } ;

/* Variables and functions */
 int bdisp_get_addr (struct bdisp_ctx*,TYPE_2__*,struct bdisp_frame*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdisp_get_bufs(struct bdisp_ctx *ctx)
{
	struct bdisp_frame *src, *dst;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	int ret;

	src = &ctx->src;
	dst = &ctx->dst;

	src_vb = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	ret = bdisp_get_addr(ctx, &src_vb->vb2_buf, src, src->paddr);
	if (ret)
		return ret;

	dst_vb = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	ret = bdisp_get_addr(ctx, &dst_vb->vb2_buf, dst, dst->paddr);
	if (ret)
		return ret;

	dst_vb->vb2_buf.timestamp = src_vb->vb2_buf.timestamp;

	return 0;
}