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
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct vim2m_ctx {int /*<<< orphan*/  transtime; int /*<<< orphan*/  work_run; int /*<<< orphan*/  hdl; TYPE_3__ fh; } ;
struct TYPE_4__ {int /*<<< orphan*/  req; } ;
struct TYPE_5__ {TYPE_1__ req_obj; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_process (struct vim2m_ctx*,struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_run(void *priv)
{
	struct vim2m_ctx *ctx = priv;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Apply request controls if any */
	v4l2_ctrl_request_setup(src_buf->vb2_buf.req_obj.req,
				&ctx->hdl);

	device_process(ctx, src_buf, dst_buf);

	/* Complete request controls if any */
	v4l2_ctrl_request_complete(src_buf->vb2_buf.req_obj.req,
				   &ctx->hdl);

	/* Run delayed work, which simulates a hardware irq  */
	schedule_delayed_work(&ctx->work_run, msecs_to_jiffies(ctx->transtime));
}