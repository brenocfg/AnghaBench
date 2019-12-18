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
struct TYPE_2__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {int pixel_format; TYPE_1__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLEGRO_HEIGHT_MAX ; 
 int /*<<< orphan*/  ALLEGRO_HEIGHT_MIN ; 
 int /*<<< orphan*/  ALLEGRO_WIDTH_MAX ; 
 int /*<<< orphan*/  ALLEGRO_WIDTH_MIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
#define  V4L2_PIX_FMT_H264 129 
#define  V4L2_PIX_FMT_NV12 128 

__attribute__((used)) static int allegro_enum_framesizes(struct file *file, void *fh,
				   struct v4l2_frmsizeenum *fsize)
{
	switch (fsize->pixel_format) {
	case V4L2_PIX_FMT_H264:
	case V4L2_PIX_FMT_NV12:
		break;
	default:
		return -EINVAL;
	}

	if (fsize->index)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = ALLEGRO_WIDTH_MIN;
	fsize->stepwise.max_width = ALLEGRO_WIDTH_MAX;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = ALLEGRO_HEIGHT_MIN;
	fsize->stepwise.max_height = ALLEGRO_HEIGHT_MAX;
	fsize->stepwise.step_height = 1;

	return 0;
}