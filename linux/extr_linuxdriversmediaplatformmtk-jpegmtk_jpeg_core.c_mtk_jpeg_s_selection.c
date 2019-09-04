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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_2__ r; } ;
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct mtk_jpeg_ctx {TYPE_1__ out_q; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 128 
 struct mtk_jpeg_ctx* mtk_jpeg_fh_to_ctx (void*) ; 

__attribute__((used)) static int mtk_jpeg_s_selection(struct file *file, void *priv,
				struct v4l2_selection *s)
{
	struct mtk_jpeg_ctx *ctx = mtk_jpeg_fh_to_ctx(priv);

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = ctx->out_q.w;
		s->r.height = ctx->out_q.h;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}