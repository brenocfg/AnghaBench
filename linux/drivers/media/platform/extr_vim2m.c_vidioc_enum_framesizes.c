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
struct TYPE_2__ {int /*<<< orphan*/  step_height; int /*<<< orphan*/  step_width; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct v4l2_frmsizeenum {scalar_t__ index; TYPE_1__ stepwise; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_H ; 
 int /*<<< orphan*/  MAX_W ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_STEPWISE ; 
 int /*<<< orphan*/  find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *file, void *priv,
				  struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index != 0)
		return -EINVAL;

	if (!find_format(fsize->pixel_format))
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = MIN_W;
	fsize->stepwise.min_height = MIN_H;
	fsize->stepwise.max_width = MAX_W;
	fsize->stepwise.max_height = MAX_H;

	get_alignment(fsize->pixel_format,
		      &fsize->stepwise.step_width,
		      &fsize->stepwise.step_height);
	return 0;
}