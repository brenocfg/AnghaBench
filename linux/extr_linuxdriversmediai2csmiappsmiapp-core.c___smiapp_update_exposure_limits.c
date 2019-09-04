#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int /*<<< orphan*/  step; int /*<<< orphan*/  minimum; } ;
struct smiapp_sensor {int* limits; TYPE_3__* vblank; TYPE_2__* pixel_array; struct v4l2_ctrl* exposure; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_5__ {TYPE_1__* crop; } ;
struct TYPE_4__ {int height; } ;

/* Variables and functions */
 size_t SMIAPP_LIMIT_COARSE_INTEGRATION_TIME_MAX_MARGIN ; 
 size_t SMIAPP_PA_PAD_SRC ; 
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (struct v4l2_ctrl*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __smiapp_update_exposure_limits(struct smiapp_sensor *sensor)
{
	struct v4l2_ctrl *ctrl = sensor->exposure;
	int max;

	max = sensor->pixel_array->crop[SMIAPP_PA_PAD_SRC].height
		+ sensor->vblank->val
		- sensor->limits[SMIAPP_LIMIT_COARSE_INTEGRATION_TIME_MAX_MARGIN];

	__v4l2_ctrl_modify_range(ctrl, ctrl->minimum, max, ctrl->step, max);
}