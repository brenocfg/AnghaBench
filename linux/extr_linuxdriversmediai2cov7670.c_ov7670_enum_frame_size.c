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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {int index; scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct ov7670_win_size {scalar_t__ width; scalar_t__ height; } ;
struct ov7670_info {scalar_t__ min_width; scalar_t__ min_height; TYPE_1__* devtype; } ;
typedef  int __u32 ;
struct TYPE_2__ {unsigned int n_win_sizes; struct ov7670_win_size* win_sizes; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_enum_frame_size(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_frame_size_enum *fse)
{
	struct ov7670_info *info = to_state(sd);
	int i;
	int num_valid = -1;
	__u32 index = fse->index;
	unsigned int n_win_sizes = info->devtype->n_win_sizes;

	if (fse->pad)
		return -EINVAL;

	/*
	 * If a minimum width/height was requested, filter out the capture
	 * windows that fall outside that.
	 */
	for (i = 0; i < n_win_sizes; i++) {
		struct ov7670_win_size *win = &info->devtype->win_sizes[i];
		if (info->min_width && win->width < info->min_width)
			continue;
		if (info->min_height && win->height < info->min_height)
			continue;
		if (index == ++num_valid) {
			fse->min_width = fse->max_width = win->width;
			fse->min_height = fse->max_height = win->height;
			return 0;
		}
	}

	return -EINVAL;
}