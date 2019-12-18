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
struct vicodec_ctx {int /*<<< orphan*/  hdl; } ;
struct TYPE_2__ {int /*<<< orphan*/  req; } ;
struct vb2_buffer {TYPE_1__ req_obj; int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vicodec_ctx* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vicodec_buf_request_complete(struct vb2_buffer *vb)
{
	struct vicodec_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &ctx->hdl);
}