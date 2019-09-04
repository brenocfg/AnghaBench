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
struct v4l2_subdev_frame_interval_enum {size_t index; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {scalar_t__ width; scalar_t__ height; } ;
struct s5k6aa_interval {int /*<<< orphan*/  interval; TYPE_1__ size; } ;
struct s5k6aa {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct s5k6aa_interval*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  S5K6AA_WIN_HEIGHT_MAX ; 
 int /*<<< orphan*/  S5K6AA_WIN_HEIGHT_MIN ; 
 int /*<<< orphan*/  S5K6AA_WIN_WIDTH_MAX ; 
 int /*<<< orphan*/  S5K6AA_WIN_WIDTH_MIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k6aa_interval* s5k6aa_intervals ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_enum_frame_interval(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_frame_interval_enum *fie)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	const struct s5k6aa_interval *fi;
	int ret = 0;

	if (fie->index >= ARRAY_SIZE(s5k6aa_intervals))
		return -EINVAL;

	v4l_bound_align_image(&fie->width, S5K6AA_WIN_WIDTH_MIN,
			      S5K6AA_WIN_WIDTH_MAX, 1,
			      &fie->height, S5K6AA_WIN_HEIGHT_MIN,
			      S5K6AA_WIN_HEIGHT_MAX, 1, 0);

	mutex_lock(&s5k6aa->lock);
	fi = &s5k6aa_intervals[fie->index];
	if (fie->width > fi->size.width || fie->height > fi->size.height)
		ret = -EINVAL;
	else
		fie->interval = fi->interval;
	mutex_unlock(&s5k6aa->lock);

	return ret;
}