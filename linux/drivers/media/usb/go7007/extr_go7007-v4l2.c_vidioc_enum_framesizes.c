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
struct TYPE_2__ {int width; int height; } ;
struct v4l2_frmsizeenum {int index; TYPE_1__ discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; } ;
struct go7007 {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  get_resolution (struct go7007*,int*,int*) ; 
 int /*<<< orphan*/  valid_pixelformat (int /*<<< orphan*/ ) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *filp, void *priv,
				  struct v4l2_frmsizeenum *fsize)
{
	struct go7007 *go = video_drvdata(filp);
	int width, height;

	if (fsize->index > 2)
		return -EINVAL;

	if (!valid_pixelformat(fsize->pixel_format))
		return -EINVAL;

	get_resolution(go, &width, &height);
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = (width >> fsize->index) & ~0xf;
	fsize->discrete.height = (height >> fsize->index) & ~0xf;
	return 0;
}