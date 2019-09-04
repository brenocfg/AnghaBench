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
struct TYPE_3__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {int flags; TYPE_1__ vb2_buf; int /*<<< orphan*/  timecode; } ;
struct rockchip_rga {int /*<<< orphan*/  m2m_dev; struct rga_ctx* curr; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct rga_ctx {TYPE_2__ fh; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RGA_INT ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  rga_mod (struct rockchip_rga*,int /*<<< orphan*/ ,int,int) ; 
 int rga_read (struct rockchip_rga*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rga_isr(int irq, void *prv)
{
	struct rockchip_rga *rga = prv;
	int intr;

	intr = rga_read(rga, RGA_INT) & 0xf;

	rga_mod(rga, RGA_INT, intr << 4, 0xf << 4);

	if (intr & 0x04) {
		struct vb2_v4l2_buffer *src, *dst;
		struct rga_ctx *ctx = rga->curr;

		WARN_ON(!ctx);

		rga->curr = NULL;

		src = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		dst = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

		WARN_ON(!src);
		WARN_ON(!dst);

		dst->timecode = src->timecode;
		dst->vb2_buf.timestamp = src->vb2_buf.timestamp;
		dst->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst->flags |= src->flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_done(src, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_done(dst, VB2_BUF_STATE_DONE);
		v4l2_m2m_job_finish(rga->m2m_dev, ctx->fh.m2m_ctx);
	}

	return IRQ_HANDLED;
}