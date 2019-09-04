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
struct fimc_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  offs_v; int /*<<< orphan*/  offs_h; int /*<<< orphan*/  o_height; int /*<<< orphan*/  o_width; } ;
struct TYPE_3__ {struct fimc_ctx* ctx; } ;
struct fimc_dev {TYPE_1__ vid_cap; } ;
struct fimc_ctx {struct fimc_frame d_frame; struct fimc_frame s_frame; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct fimc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_cap_g_selection(struct file *file, void *fh,
				struct v4l2_selection *s)
{
	struct fimc_dev *fimc = video_drvdata(file);
	struct fimc_ctx *ctx = fimc->vid_cap.ctx;
	struct fimc_frame *f = &ctx->s_frame;

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		f = &ctx->d_frame;
		/* fall through */
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = f->o_width;
		s->r.height = f->o_height;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
		f = &ctx->d_frame;
		/* fall through */
	case V4L2_SEL_TGT_CROP:
		s->r.left = f->offs_h;
		s->r.top = f->offs_v;
		s->r.width = f->width;
		s->r.height = f->height;
		return 0;
	}

	return -EINVAL;
}