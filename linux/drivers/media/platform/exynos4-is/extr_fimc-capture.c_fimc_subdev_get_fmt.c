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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; int pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct fimc_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* fmt; } ;
struct TYPE_4__ {struct v4l2_mbus_framefmt ci_fmt; struct v4l2_mbus_framefmt wb_fmt; struct fimc_ctx* ctx; } ;
struct fimc_dev {int /*<<< orphan*/  lock; TYPE_2__ vid_cap; } ;
struct fimc_ctx {struct fimc_frame s_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
#define  FIMC_SD_PAD_SINK_CAM 130 
#define  FIMC_SD_PAD_SINK_FIFO 129 
#define  FIMC_SD_PAD_SOURCE 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fimc_dev* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int) ; 

__attribute__((used)) static int fimc_subdev_get_fmt(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_format *fmt)
{
	struct fimc_dev *fimc = v4l2_get_subdevdata(sd);
	struct fimc_ctx *ctx = fimc->vid_cap.ctx;
	struct fimc_frame *ff = &ctx->s_frame;
	struct v4l2_mbus_framefmt *mf;

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		mf = v4l2_subdev_get_try_format(sd, cfg, fmt->pad);
		fmt->format = *mf;
		return 0;
	}

	mf = &fmt->format;
	mutex_lock(&fimc->lock);

	switch (fmt->pad) {
	case FIMC_SD_PAD_SOURCE:
		if (!WARN_ON(ff->fmt == NULL))
			mf->code = ff->fmt->mbus_code;
		/* Sink pads crop rectangle size */
		mf->width = ff->width;
		mf->height = ff->height;
		break;
	case FIMC_SD_PAD_SINK_FIFO:
		*mf = fimc->vid_cap.wb_fmt;
		break;
	case FIMC_SD_PAD_SINK_CAM:
	default:
		*mf = fimc->vid_cap.ci_fmt;
		break;
	}

	mutex_unlock(&fimc->lock);
	mf->colorspace = V4L2_COLORSPACE_JPEG;

	return 0;
}