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
struct v4l2_subdev {int dummy; } ;
struct v4l2_bt_timings {int /*<<< orphan*/  width; int /*<<< orphan*/  standards; } ;
struct v4l2_dv_timings {scalar_t__ type; struct v4l2_bt_timings bt; } ;
struct tvp7002 {TYPE_2__* current_timings; } ;
struct TYPE_3__ {struct v4l2_bt_timings bt; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_settings; TYPE_1__ timings; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_TIMINGS ; 
 scalar_t__ V4L2_DV_BT_656_1120 ; 
 int /*<<< orphan*/  memcmp (struct v4l2_bt_timings const*,struct v4l2_bt_timings const*,int) ; 
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 
 TYPE_2__* tvp7002_timings ; 
 int tvp7002_write_inittab (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvp7002_s_dv_timings(struct v4l2_subdev *sd,
					struct v4l2_dv_timings *dv_timings)
{
	struct tvp7002 *device = to_tvp7002(sd);
	const struct v4l2_bt_timings *bt = &dv_timings->bt;
	int i;

	if (dv_timings->type != V4L2_DV_BT_656_1120)
		return -EINVAL;
	for (i = 0; i < NUM_TIMINGS; i++) {
		const struct v4l2_bt_timings *t = &tvp7002_timings[i].timings.bt;

		if (!memcmp(bt, t, &bt->standards - &bt->width)) {
			device->current_timings = &tvp7002_timings[i];
			return tvp7002_write_inittab(sd, tvp7002_timings[i].p_settings);
		}
	}
	return -EINVAL;
}