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
struct vb2_buffer {TYPE_2__* vb2_queue; } ;
struct bdisp_frame {int /*<<< orphan*/  sizeimage; } ;
struct bdisp_ctx {TYPE_1__* bdisp_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bdisp_frame*) ; 
 int PTR_ERR (struct bdisp_frame*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct bdisp_frame* ctx_get_frame (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct bdisp_frame*) ; 
 struct bdisp_ctx* vb2_get_drv_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdisp_buf_prepare(struct vb2_buffer *vb)
{
	struct bdisp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct bdisp_frame *frame = ctx_get_frame(ctx, vb->vb2_queue->type);

	if (IS_ERR(frame)) {
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		return PTR_ERR(frame);
	}

	if (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		vb2_set_plane_payload(vb, 0, frame->sizeimage);

	return 0;
}