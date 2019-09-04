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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct rockchip_rga {int /*<<< orphan*/  ctrl_lock; struct rga_ctx* curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct rga_ctx {TYPE_1__ fh; struct rockchip_rga* rga; } ;

/* Variables and functions */
 int /*<<< orphan*/  rga_buf_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rga_hw_start (struct rockchip_rga*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_run(void *prv)
{
	struct rga_ctx *ctx = prv;
	struct rockchip_rga *rga = ctx->rga;
	struct vb2_v4l2_buffer *src, *dst;
	unsigned long flags;

	spin_lock_irqsave(&rga->ctrl_lock, flags);

	rga->curr = ctx;

	src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	rga_buf_map(&src->vb2_buf);
	rga_buf_map(&dst->vb2_buf);

	rga_hw_start(rga);

	spin_unlock_irqrestore(&rga->ctrl_lock, flags);
}