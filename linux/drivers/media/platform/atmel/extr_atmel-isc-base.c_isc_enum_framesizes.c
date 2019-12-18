#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_frame_size_enum {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  index; } ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; TYPE_5__ discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct TYPE_11__ {TYPE_3__* sd_format; } ;
struct isc_device {int num_user_formats; TYPE_4__ config; TYPE_2__* current_subdev; TYPE_1__** user_formats; } ;
struct file {int dummy; } ;
struct TYPE_13__ {scalar_t__ fourcc; } ;
struct TYPE_10__ {int /*<<< orphan*/  mbus_code; } ;
struct TYPE_9__ {int /*<<< orphan*/  sd; } ;
struct TYPE_8__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 TYPE_6__* controller_formats ; 
 int /*<<< orphan*/  enum_frame_size ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 
 struct isc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int isc_enum_framesizes(struct file *file, void *fh,
			       struct v4l2_frmsizeenum *fsize)
{
	struct isc_device *isc = video_drvdata(file);
	struct v4l2_subdev_frame_size_enum fse = {
		.index = fsize->index,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret = -EINVAL;
	int i;

	for (i = 0; i < isc->num_user_formats; i++)
		if (isc->user_formats[i]->fourcc == fsize->pixel_format)
			ret = 0;

	for (i = 0; i < ARRAY_SIZE(controller_formats); i++)
		if (controller_formats[i].fourcc == fsize->pixel_format)
			ret = 0;

	if (ret)
		return ret;

	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, enum_frame_size,
			       NULL, &fse);
	if (ret)
		return ret;

	fse.code = isc->config.sd_format->mbus_code;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = fse.max_width;
	fsize->discrete.height = fse.max_height;

	return 0;
}