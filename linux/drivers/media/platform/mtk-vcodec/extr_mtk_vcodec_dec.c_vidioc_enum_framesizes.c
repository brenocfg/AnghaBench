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
struct TYPE_5__ {int /*<<< orphan*/  step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  step_width; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; scalar_t__ pixel_format; TYPE_2__ stepwise; int /*<<< orphan*/  type; } ;
struct mtk_vcodec_ctx {TYPE_1__* dev; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ fourcc; TYPE_2__ stepwise; } ;
struct TYPE_4__ {int dec_capability; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_SUPPORTED_FRAMESIZE ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
 int VCODEC_CAPABILITY_4K_DISABLED ; 
 int /*<<< orphan*/  VCODEC_DEC_4K_CODED_HEIGHT ; 
 int /*<<< orphan*/  VCODEC_DEC_4K_CODED_WIDTH ; 
 struct mtk_vcodec_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int,char*,...) ; 
 TYPE_3__* mtk_vdec_framesizes ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *file, void *priv,
				struct v4l2_frmsizeenum *fsize)
{
	int i = 0;
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	if (fsize->index != 0)
		return -EINVAL;

	for (i = 0; i < NUM_SUPPORTED_FRAMESIZE; ++i) {
		if (fsize->pixel_format != mtk_vdec_framesizes[i].fourcc)
			continue;

		fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
		fsize->stepwise = mtk_vdec_framesizes[i].stepwise;
		if (!(ctx->dev->dec_capability &
				VCODEC_CAPABILITY_4K_DISABLED)) {
			mtk_v4l2_debug(3, "4K is enabled");
			fsize->stepwise.max_width =
					VCODEC_DEC_4K_CODED_WIDTH;
			fsize->stepwise.max_height =
					VCODEC_DEC_4K_CODED_HEIGHT;
		}
		mtk_v4l2_debug(1, "%x, %d %d %d %d %d %d",
				ctx->dev->dec_capability,
				fsize->stepwise.min_width,
				fsize->stepwise.max_width,
				fsize->stepwise.step_width,
				fsize->stepwise.min_height,
				fsize->stepwise.max_height,
				fsize->stepwise.step_height);
		return 0;
	}

	return -EINVAL;
}