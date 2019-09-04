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
struct TYPE_4__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct v4l2_frmivalenum {int index; int width; int height; TYPE_2__ discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; } ;
struct go7007 {int /*<<< orphan*/  sensor_framerate; TYPE_1__* board_info; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int sensor_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GO7007_SENSOR_SCALING ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  get_resolution (struct go7007*,int*,int*) ; 
 int /*<<< orphan*/  valid_pixelformat (int /*<<< orphan*/ ) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_frameintervals(struct file *filp, void *priv,
				      struct v4l2_frmivalenum *fival)
{
	struct go7007 *go = video_drvdata(filp);
	int width, height;
	int i;

	if (fival->index > 4)
		return -EINVAL;

	if (!valid_pixelformat(fival->pixel_format))
		return -EINVAL;

	if (!(go->board_info->sensor_flags & GO7007_SENSOR_SCALING)) {
		get_resolution(go, &width, &height);
		for (i = 0; i <= 2; i++)
			if (fival->width == ((width >> i) & ~0xf) &&
			    fival->height == ((height >> i) & ~0xf))
				break;
		if (i > 2)
			return -EINVAL;
	}
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete.numerator = 1001 * (fival->index + 1);
	fival->discrete.denominator = go->sensor_framerate;
	return 0;
}