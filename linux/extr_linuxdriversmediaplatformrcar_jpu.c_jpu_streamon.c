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
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
struct jpu_q_data {TYPE_3__ format; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_2__ fh; TYPE_1__* jpu; scalar_t__ encoder; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  __jpu_try_fmt (struct jpu_ctx*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct jpu_ctx* fh_to_ctx (void*) ; 
 struct jpu_q_data* jpu_get_q_data (struct jpu_ctx*,int) ; 
 int v4l2_m2m_streamon (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jpu_streamon(struct file *file, void *priv, enum v4l2_buf_type type)
{
	struct jpu_ctx *ctx = fh_to_ctx(priv);
	struct jpu_q_data *src_q_data, *dst_q_data, *orig, adj, *ref;
	enum v4l2_buf_type adj_type;

	src_q_data = jpu_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	dst_q_data = jpu_get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

	if (ctx->encoder) {
		adj = *src_q_data;
		orig = src_q_data;
		ref = dst_q_data;
		adj_type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	} else {
		adj = *dst_q_data;
		orig = dst_q_data;
		ref = src_q_data;
		adj_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}

	adj.format.width = ref->format.width;
	adj.format.height = ref->format.height;

	__jpu_try_fmt(ctx, NULL, &adj.format, adj_type);

	if (adj.format.width != orig->format.width ||
	    adj.format.height != orig->format.height) {
		dev_err(ctx->jpu->dev, "src and dst formats do not match.\n");
		/* maybe we can return -EPIPE here? */
		return -EINVAL;
	}

	return v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
}