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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; scalar_t__ height; scalar_t__ width; } ;
struct v4l2_subdev_format {scalar_t__ pad; scalar_t__ which; struct v4l2_mbus_framefmt format; } ;
struct fimc_isp {struct v4l2_mbus_framefmt sink_fmt; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 scalar_t__ FIMC_ISP_CAC_MARGIN_HEIGHT ; 
 scalar_t__ FIMC_ISP_CAC_MARGIN_WIDTH ; 
 scalar_t__ FIMC_ISP_SD_PAD_SINK ; 
 scalar_t__ FIMC_ISP_SD_PAD_SRC_FIFO ; 
 int /*<<< orphan*/  FIMC_ISP_SINK_HEIGHT_MAX ; 
 int /*<<< orphan*/  FIMC_ISP_SINK_HEIGHT_MIN ; 
 int /*<<< orphan*/  FIMC_ISP_SINK_WIDTH_MAX ; 
 int /*<<< orphan*/  FIMC_ISP_SINK_WIDTH_MIN ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUV10_1X30 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,scalar_t__) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __isp_subdev_try_format(struct fimc_isp *isp,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_format *fmt)
{
	struct v4l2_mbus_framefmt *mf = &fmt->format;
	struct v4l2_mbus_framefmt *format;

	mf->colorspace = V4L2_COLORSPACE_SRGB;

	if (fmt->pad == FIMC_ISP_SD_PAD_SINK) {
		v4l_bound_align_image(&mf->width, FIMC_ISP_SINK_WIDTH_MIN,
				FIMC_ISP_SINK_WIDTH_MAX, 0,
				&mf->height, FIMC_ISP_SINK_HEIGHT_MIN,
				FIMC_ISP_SINK_HEIGHT_MAX, 0, 0);
		mf->code = MEDIA_BUS_FMT_SGRBG10_1X10;
	} else {
		if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
			format = v4l2_subdev_get_try_format(&isp->subdev, cfg,
						FIMC_ISP_SD_PAD_SINK);
		else
			format = &isp->sink_fmt;

		/* Allow changing format only on sink pad */
		mf->width = format->width - FIMC_ISP_CAC_MARGIN_WIDTH;
		mf->height = format->height - FIMC_ISP_CAC_MARGIN_HEIGHT;

		if (fmt->pad == FIMC_ISP_SD_PAD_SRC_FIFO) {
			mf->code = MEDIA_BUS_FMT_YUV10_1X30;
			mf->colorspace = V4L2_COLORSPACE_JPEG;
		} else {
			mf->code = format->code;
		}
	}
}