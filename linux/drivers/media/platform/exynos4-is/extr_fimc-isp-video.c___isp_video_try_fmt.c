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
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  num_planes; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct fimc_isp {int dummy; } ;
struct fimc_fmt {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  memplanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIMC_ISP_SOURCE_HEIGHT_MAX ; 
 int /*<<< orphan*/  FIMC_ISP_SOURCE_HEIGHT_MIN ; 
 int /*<<< orphan*/  FIMC_ISP_SOURCE_WIDTH_MAX ; 
 int /*<<< orphan*/  FIMC_ISP_SOURCE_WIDTH_MIN ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct fimc_fmt* fimc_isp_find_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __isp_video_try_fmt(struct fimc_isp *isp,
				struct v4l2_pix_format_mplane *pixm,
				const struct fimc_fmt **fmt)
{
	const struct fimc_fmt *__fmt;

	__fmt = fimc_isp_find_format(&pixm->pixelformat, NULL, 2);

	if (fmt)
		*fmt = __fmt;

	pixm->colorspace = V4L2_COLORSPACE_SRGB;
	pixm->field = V4L2_FIELD_NONE;
	pixm->num_planes = __fmt->memplanes;
	pixm->pixelformat = __fmt->fourcc;
	/*
	 * TODO: double check with the docmentation these width/height
	 * constraints are correct.
	 */
	v4l_bound_align_image(&pixm->width, FIMC_ISP_SOURCE_WIDTH_MIN,
			      FIMC_ISP_SOURCE_WIDTH_MAX, 3,
			      &pixm->height, FIMC_ISP_SOURCE_HEIGHT_MIN,
			      FIMC_ISP_SOURCE_HEIGHT_MAX, 0, 0);
}