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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_4__ {scalar_t__ m2m_ctx; } ;
struct bdisp_ctx {TYPE_2__ fh; TYPE_1__* bdisp_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_queue (scalar_t__,struct vb2_v4l2_buffer*) ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct bdisp_ctx* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdisp_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct bdisp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);

	/* return to V4L2 any 0-size buffer so it can be dequeued by user */
	if (!vb2_get_plane_payload(vb, 0)) {
		dev_dbg(ctx->bdisp_dev->dev, "0 data buffer, skip it\n");
		vb2_buffer_done(vb, VB2_BUF_STATE_DONE);
		return;
	}

	if (ctx->fh.m2m_ctx)
		v4l2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}