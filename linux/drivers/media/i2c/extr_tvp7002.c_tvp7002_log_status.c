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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_bt_timings {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct tvp7002 {int /*<<< orphan*/  hdl; scalar_t__ streaming; TYPE_2__* current_timings; } ;
struct TYPE_7__ {struct v4l2_bt_timings bt; } ;
struct TYPE_8__ {TYPE_3__ timings; } ;
struct TYPE_5__ {struct v4l2_bt_timings bt; } ;
struct TYPE_6__ {TYPE_1__ timings; } ;

/* Variables and functions */
 int NUM_TIMINGS ; 
 struct tvp7002* to_tvp7002 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp7002_query_dv (struct v4l2_subdev*,int*) ; 
 TYPE_4__* tvp7002_timings ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int tvp7002_log_status(struct v4l2_subdev *sd)
{
	struct tvp7002 *device = to_tvp7002(sd);
	const struct v4l2_bt_timings *bt;
	int detected;

	/* Find my current timings */
	tvp7002_query_dv(sd, &detected);

	bt = &device->current_timings->timings.bt;
	v4l2_info(sd, "Selected DV Timings: %ux%u\n", bt->width, bt->height);
	if (detected == NUM_TIMINGS) {
		v4l2_info(sd, "Detected DV Timings: None\n");
	} else {
		bt = &tvp7002_timings[detected].timings.bt;
		v4l2_info(sd, "Detected DV Timings: %ux%u\n",
				bt->width, bt->height);
	}
	v4l2_info(sd, "Streaming enabled: %s\n",
					device->streaming ? "yes" : "no");

	/* Print the current value of the gain control */
	v4l2_ctrl_handler_log_status(&device->hdl, sd->name);

	return 0;
}