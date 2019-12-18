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
struct TYPE_3__ {int /*<<< orphan*/  req; } ;
struct TYPE_4__ {TYPE_1__ req_obj; } ;
struct vb2_v4l2_buffer {TYPE_2__ vb2_buf; } ;
struct hantro_ctx {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hantro_prepare_run(struct hantro_ctx *ctx)
{
	struct vb2_v4l2_buffer *src_buf;

	src_buf = hantro_get_src_buf(ctx);
	v4l2_ctrl_request_setup(src_buf->vb2_buf.req_obj.req,
				&ctx->ctrl_handler);
}