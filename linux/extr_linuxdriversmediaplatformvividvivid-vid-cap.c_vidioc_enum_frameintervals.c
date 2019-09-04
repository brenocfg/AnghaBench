#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vivid_fmt {int dummy; } ;
struct vivid_dev {int /*<<< orphan*/  timeperframe_vid_cap; } ;
struct v4l2_frmivalenum {int index; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  discrete; void* type; int /*<<< orphan*/  pixel_format; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int MAX_HEIGHT ; 
 int MAX_WIDTH ; 
 int MAX_ZOOM ; 
 scalar_t__ MIN_HEIGHT ; 
 scalar_t__ MIN_WIDTH ; 
 void* V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int VIVID_WEBCAM_SIZES ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 struct vivid_fmt* vivid_get_format (struct vivid_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vivid_is_webcam (struct vivid_dev*) ; 
 int /*<<< orphan*/ * webcam_intervals ; 
 TYPE_1__* webcam_sizes ; 

int vidioc_enum_frameintervals(struct file *file, void *priv,
					     struct v4l2_frmivalenum *fival)
{
	struct vivid_dev *dev = video_drvdata(file);
	const struct vivid_fmt *fmt;
	int i;

	fmt = vivid_get_format(dev, fival->pixel_format);
	if (!fmt)
		return -EINVAL;

	if (!vivid_is_webcam(dev)) {
		if (fival->index)
			return -EINVAL;
		if (fival->width < MIN_WIDTH || fival->width > MAX_WIDTH * MAX_ZOOM)
			return -EINVAL;
		if (fival->height < MIN_HEIGHT || fival->height > MAX_HEIGHT * MAX_ZOOM)
			return -EINVAL;
		fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
		fival->discrete = dev->timeperframe_vid_cap;
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(webcam_sizes); i++)
		if (fival->width == webcam_sizes[i].width &&
		    fival->height == webcam_sizes[i].height)
			break;
	if (i == ARRAY_SIZE(webcam_sizes))
		return -EINVAL;
	if (fival->index >= 2 * (VIVID_WEBCAM_SIZES - i))
		return -EINVAL;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = webcam_intervals[fival->index];
	return 0;
}