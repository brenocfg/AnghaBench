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
struct TYPE_2__ {int /*<<< orphan*/  luma; } ;
struct vicodec_ctx {int /*<<< orphan*/  ctrl_gop_size; int /*<<< orphan*/  compressed_frame; TYPE_1__ ref_frame; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 struct vicodec_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vicodec_return_bufs (struct vb2_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vicodec_stop_streaming(struct vb2_queue *q)
{
	struct vicodec_ctx *ctx = vb2_get_drv_priv(q);

	vicodec_return_bufs(q, VB2_BUF_STATE_ERROR);

	if (!V4L2_TYPE_IS_OUTPUT(q->type))
		return;

	kvfree(ctx->ref_frame.luma);
	kvfree(ctx->compressed_frame);
	v4l2_ctrl_grab(ctx->ctrl_gop_size, false);
}