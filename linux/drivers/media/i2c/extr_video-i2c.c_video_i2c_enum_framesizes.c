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
struct video_i2c_data {TYPE_3__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; scalar_t__ pixel_format; TYPE_2__ discrete; int /*<<< orphan*/  type; } ;
struct v4l2_frmsize_discrete {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct file {int dummy; } ;
struct TYPE_6__ {TYPE_1__* format; struct v4l2_frmsize_discrete* size; } ;
struct TYPE_4__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 struct video_i2c_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_i2c_enum_framesizes(struct file *file, void *fh,
				       struct v4l2_frmsizeenum *fsize)
{
	const struct video_i2c_data *data = video_drvdata(file);
	const struct v4l2_frmsize_discrete *size = data->chip->size;

	/* currently only one frame size is allowed */
	if (fsize->index > 0)
		return -EINVAL;

	if (fsize->pixel_format != data->chip->format->pixelformat)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = size->width;
	fsize->discrete.height = size->height;

	return 0;
}