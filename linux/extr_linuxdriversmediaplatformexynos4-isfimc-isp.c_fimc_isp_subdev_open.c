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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_PREVIEW_STILL_HEIGHT ; 
 scalar_t__ DEFAULT_PREVIEW_STILL_WIDTH ; 
 scalar_t__ FIMC_ISP_CAC_MARGIN_HEIGHT ; 
 scalar_t__ FIMC_ISP_CAC_MARGIN_WIDTH ; 
 int /*<<< orphan*/  FIMC_ISP_SD_PAD_SINK ; 
 int /*<<< orphan*/  FIMC_ISP_SD_PAD_SRC_DMA ; 
 int /*<<< orphan*/  FIMC_ISP_SD_PAD_SRC_FIFO ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_1__* fimc_isp_formats ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_isp_subdev_open(struct v4l2_subdev *sd,
				struct v4l2_subdev_fh *fh)
{
	struct v4l2_mbus_framefmt *format;
	struct v4l2_mbus_framefmt fmt = {
		.colorspace = V4L2_COLORSPACE_SRGB,
		.code = fimc_isp_formats[0].mbus_code,
		.width = DEFAULT_PREVIEW_STILL_WIDTH + FIMC_ISP_CAC_MARGIN_WIDTH,
		.height = DEFAULT_PREVIEW_STILL_HEIGHT + FIMC_ISP_CAC_MARGIN_HEIGHT,
		.field = V4L2_FIELD_NONE,
	};

	format = v4l2_subdev_get_try_format(sd, fh->pad, FIMC_ISP_SD_PAD_SINK);
	*format = fmt;

	format = v4l2_subdev_get_try_format(sd, fh->pad, FIMC_ISP_SD_PAD_SRC_FIFO);
	fmt.width = DEFAULT_PREVIEW_STILL_WIDTH;
	fmt.height = DEFAULT_PREVIEW_STILL_HEIGHT;
	*format = fmt;

	format = v4l2_subdev_get_try_format(sd, fh->pad, FIMC_ISP_SD_PAD_SRC_DMA);
	*format = fmt;

	return 0;
}