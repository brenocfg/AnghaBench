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
struct vim2m_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vim2m_ctx {int /*<<< orphan*/  transtime; TYPE_1__ fh; struct vim2m_dev* dev; } ;
struct vb2_v4l2_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_process (struct vim2m_ctx*,struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  schedule_irq (struct vim2m_dev*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_run(void *priv)
{
	struct vim2m_ctx *ctx = priv;
	struct vim2m_dev *dev = ctx->dev;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	device_process(ctx, src_buf, dst_buf);

	/* Run a timer, which simulates a hardware irq  */
	schedule_irq(dev, ctx->transtime);
}