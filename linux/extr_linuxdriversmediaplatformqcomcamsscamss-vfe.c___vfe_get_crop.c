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
struct v4l2_rect {int dummy; } ;
struct vfe_line {struct v4l2_rect crop; int /*<<< orphan*/  subdev; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int /*<<< orphan*/  MSM_VFE_PAD_SRC ; 
 int V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct v4l2_rect *
__vfe_get_crop(struct vfe_line *line,
	       struct v4l2_subdev_pad_config *cfg,
	       enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_crop(&line->subdev, cfg,
						MSM_VFE_PAD_SRC);

	return &line->crop;
}