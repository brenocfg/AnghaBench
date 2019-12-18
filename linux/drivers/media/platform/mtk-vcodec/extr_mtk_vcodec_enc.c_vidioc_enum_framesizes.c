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
struct v4l2_frmsizeenum {scalar_t__ index; scalar_t__ pixel_format; int /*<<< orphan*/  stepwise; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ fourcc; int /*<<< orphan*/  stepwise; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_SUPPORTED_FRAMESIZE ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
 TYPE_1__* mtk_venc_framesizes ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *file, void *fh,
				  struct v4l2_frmsizeenum *fsize)
{
	int i = 0;

	if (fsize->index != 0)
		return -EINVAL;

	for (i = 0; i < NUM_SUPPORTED_FRAMESIZE; ++i) {
		if (fsize->pixel_format != mtk_venc_framesizes[i].fourcc)
			continue;

		fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
		fsize->stepwise = mtk_venc_framesizes[i].stepwise;
		return 0;
	}

	return -EINVAL;
}