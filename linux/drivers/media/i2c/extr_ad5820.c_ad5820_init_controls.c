#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int error; } ;
struct TYPE_4__ {TYPE_2__* ctrl_handler; } ;
struct ad5820_device {TYPE_2__ ctrls; TYPE_1__ subdev; scalar_t__ focus_ramp_mode; scalar_t__ focus_ramp_time; scalar_t__ focus_absolute; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_FOCUS_ABSOLUTE ; 
 int /*<<< orphan*/  ad5820_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5820_init_controls(struct ad5820_device *coil)
{
	v4l2_ctrl_handler_init(&coil->ctrls, 1);

	/*
	 * V4L2_CID_FOCUS_ABSOLUTE
	 *
	 * Minimum current is 0 mA, maximum is 100 mA. Thus, 1 code is
	 * equivalent to 100/1023 = 0.0978 mA. Nevertheless, we do not use [mA]
	 * for focus position, because it is meaningless for user. Meaningful
	 * would be to use focus distance or even its inverse, but since the
	 * driver doesn't have sufficiently knowledge to do the conversion, we
	 * will just use abstract codes here. In any case, smaller value = focus
	 * position farther from camera. The default zero value means focus at
	 * infinity, and also least current consumption.
	 */
	v4l2_ctrl_new_std(&coil->ctrls, &ad5820_ctrl_ops,
			  V4L2_CID_FOCUS_ABSOLUTE, 0, 1023, 1, 0);

	if (coil->ctrls.error)
		return coil->ctrls.error;

	coil->focus_absolute = 0;
	coil->focus_ramp_time = 0;
	coil->focus_ramp_mode = 0;

	coil->subdev.ctrl_handler = &coil->ctrls;

	return 0;
}