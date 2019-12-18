#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int denominator; int numerator; } ;
struct TYPE_6__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct TYPE_8__ {TYPE_3__ max; TYPE_3__ step; TYPE_2__ min; } ;
struct v4l2_frmivalenum {scalar_t__ width; scalar_t__ height; scalar_t__ pixel_format; TYPE_4__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; } ;
struct aspeed_video {TYPE_1__ detected_timings; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_FRAME_RATE ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_CONTINUOUS ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 struct aspeed_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int aspeed_video_enum_frameintervals(struct file *file, void *fh,
					    struct v4l2_frmivalenum *fival)
{
	struct aspeed_video *video = video_drvdata(file);

	if (fival->index)
		return -EINVAL;

	if (fival->width != video->detected_timings.width ||
	    fival->height != video->detected_timings.height)
		return -EINVAL;

	if (fival->pixel_format != V4L2_PIX_FMT_JPEG)
		return -EINVAL;

	fival->type = V4L2_FRMIVAL_TYPE_CONTINUOUS;

	fival->stepwise.min.denominator = MAX_FRAME_RATE;
	fival->stepwise.min.numerator = 1;
	fival->stepwise.max.denominator = 1;
	fival->stepwise.max.numerator = 1;
	fival->stepwise.step = fival->stepwise.max;

	return 0;
}