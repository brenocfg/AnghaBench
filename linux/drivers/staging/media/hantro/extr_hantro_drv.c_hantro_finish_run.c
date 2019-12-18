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
struct TYPE_4__ {int /*<<< orphan*/  req; } ;
struct TYPE_5__ {TYPE_1__ req_obj; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;
struct hantro_ctx {TYPE_3__* dev; int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_6__ {int /*<<< orphan*/  watchdog_work; } ;

/* Variables and functions */
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hantro_finish_run(struct hantro_ctx *ctx)
{
	struct vb2_v4l2_buffer *src_buf;

	src_buf = hantro_get_src_buf(ctx);
	v4l2_ctrl_request_complete(src_buf->vb2_buf.req_obj.req,
				   &ctx->ctrl_handler);

	/* Kick the watchdog. */
	schedule_delayed_work(&ctx->dev->watchdog_work,
			      msecs_to_jiffies(2000));
}