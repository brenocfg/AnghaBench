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
struct TYPE_2__ {void* height; void* width; } ;
struct v4l2_frmsizeenum {unsigned int index; scalar_t__ pixel_format; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct pwc_device {unsigned long image_mask; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVICE_USE_CODEC23 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int PSZ_MAX ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 scalar_t__ V4L2_PIX_FMT_PWC1 ; 
 scalar_t__ V4L2_PIX_FMT_PWC2 ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 void*** pwc_image_sizes ; 
 struct pwc_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int pwc_enum_framesizes(struct file *file, void *fh,
					 struct v4l2_frmsizeenum *fsize)
{
	struct pwc_device *pdev = video_drvdata(file);
	unsigned int i = 0, index = fsize->index;

	if (fsize->pixel_format == V4L2_PIX_FMT_YUV420 ||
	    (fsize->pixel_format == V4L2_PIX_FMT_PWC1 &&
			DEVICE_USE_CODEC1(pdev->type)) ||
	    (fsize->pixel_format == V4L2_PIX_FMT_PWC2 &&
			DEVICE_USE_CODEC23(pdev->type))) {
		for (i = 0; i < PSZ_MAX; i++) {
			if (!(pdev->image_mask & (1UL << i)))
				continue;
			if (!index--) {
				fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
				fsize->discrete.width = pwc_image_sizes[i][0];
				fsize->discrete.height = pwc_image_sizes[i][1];
				return 0;
			}
		}
	}
	return -EINVAL;
}