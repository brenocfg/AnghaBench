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
struct vb2_queue {scalar_t__ type; struct bdisp_ctx* drv_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct bdisp_ctx {TYPE_1__ fh; TYPE_2__* bdisp_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdisp_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct bdisp_ctx *ctx = q->drv_priv;
	struct vb2_v4l2_buffer *buf;
	int ret = pm_runtime_get_sync(ctx->bdisp_dev->dev);

	if (ret < 0) {
		dev_err(ctx->bdisp_dev->dev, "failed to set runtime PM\n");

		if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
			while ((buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx)))
				v4l2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
		} else {
			while ((buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx)))
				v4l2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
		}

		return ret;
	}

	return 0;
}