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
struct vb2_v4l2_buffer {int dummy; } ;
struct hantro_ctx {TYPE_3__* dev; TYPE_1__* codec_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  clocks; TYPE_2__* variant; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_clocks; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* run ) (struct hantro_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int clk_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_job_finish (TYPE_3__*,struct hantro_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hantro_ctx*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_copy_metadata (struct vb2_v4l2_buffer*,struct vb2_v4l2_buffer*,int) ; 

__attribute__((used)) static void device_run(void *priv)
{
	struct hantro_ctx *ctx = priv;
	struct vb2_v4l2_buffer *src, *dst;
	int ret;

	src = hantro_get_src_buf(ctx);
	dst = hantro_get_dst_buf(ctx);

	ret = clk_bulk_enable(ctx->dev->variant->num_clocks, ctx->dev->clocks);
	if (ret)
		goto err_cancel_job;
	ret = pm_runtime_get_sync(ctx->dev->dev);
	if (ret < 0)
		goto err_cancel_job;

	v4l2_m2m_buf_copy_metadata(src, dst, true);

	ctx->codec_ops->run(ctx);
	return;

err_cancel_job:
	hantro_job_finish(ctx->dev, ctx, 0, VB2_BUF_STATE_ERROR);
}