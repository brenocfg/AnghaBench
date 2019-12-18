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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; int /*<<< orphan*/  type; TYPE_1__ discrete; scalar_t__ index; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct aspeed_video {TYPE_2__ pix_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_enum_framesizes(struct file *file, void *fh,
					struct v4l2_frmsizeenum *fsize)
{
	struct aspeed_video *video = video_drvdata(file);

	if (fsize->index)
		return -EINVAL;

	if (fsize->pixel_format != V4L2_PIX_FMT_JPEG)
		return -EINVAL;

	fsize->discrete.width = video->pix_fmt.width;
	fsize->discrete.height = video->pix_fmt.height;
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;

	return 0;
}