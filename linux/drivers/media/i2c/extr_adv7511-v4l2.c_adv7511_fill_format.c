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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct adv7511_state {TYPE_2__ dv_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

__attribute__((used)) static void adv7511_fill_format(struct adv7511_state *state,
				struct v4l2_mbus_framefmt *format)
{
	format->width = state->dv_timings.bt.width;
	format->height = state->dv_timings.bt.height;
	format->field = V4L2_FIELD_NONE;
}