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
struct TYPE_3__ {int step_width; int step_height; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {int pixel_format; TYPE_1__ stepwise; int /*<<< orphan*/  type; scalar_t__ index; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 int /*<<< orphan*/  MIN_HEIGHT ; 
 int /*<<< orphan*/  MIN_WIDTH ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
#define  V4L2_PIX_FMT_FWHT 129 
#define  V4L2_PIX_FMT_FWHT_STATELESS 128 
 TYPE_2__* find_fmt (int) ; 

__attribute__((used)) static int vicodec_enum_framesizes(struct file *file, void *fh,
				   struct v4l2_frmsizeenum *fsize)
{
	switch (fsize->pixel_format) {
	case V4L2_PIX_FMT_FWHT_STATELESS:
		break;
	case V4L2_PIX_FMT_FWHT:
		break;
	default:
		if (find_fmt(fsize->pixel_format)->id == fsize->pixel_format)
			break;
		return -EINVAL;
	}

	if (fsize->index)
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;

	fsize->stepwise.min_width = MIN_WIDTH;
	fsize->stepwise.max_width = MAX_WIDTH;
	fsize->stepwise.step_width = 8;
	fsize->stepwise.min_height = MIN_HEIGHT;
	fsize->stepwise.max_height = MAX_HEIGHT;
	fsize->stepwise.step_height = 8;

	return 0;
}