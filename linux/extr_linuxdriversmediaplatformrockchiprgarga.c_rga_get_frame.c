#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rga_frame {int dummy; } ;
struct rga_ctx {struct rga_frame out; struct rga_frame in; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rga_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 

struct rga_frame *rga_get_frame(struct rga_ctx *ctx, enum v4l2_buf_type type)
{
	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		return &ctx->in;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return &ctx->out;
	default:
		return ERR_PTR(-EINVAL);
	}
}