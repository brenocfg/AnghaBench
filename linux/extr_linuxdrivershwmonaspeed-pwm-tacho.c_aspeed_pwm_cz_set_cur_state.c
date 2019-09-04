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
struct thermal_cooling_device {struct aspeed_cooling_device* devdata; } ;
struct aspeed_cooling_device {unsigned long max_state; unsigned long cur_state; size_t pwm_port; int /*<<< orphan*/ * cooling_levels; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pwm_port_fan_ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  aspeed_set_pwm_port_fan_ctrl (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aspeed_pwm_cz_set_cur_state(struct thermal_cooling_device *tcdev,
			    unsigned long state)
{
	struct aspeed_cooling_device *cdev = tcdev->devdata;

	if (state > cdev->max_state)
		return -EINVAL;

	cdev->cur_state = state;
	cdev->priv->pwm_port_fan_ctrl[cdev->pwm_port] =
					cdev->cooling_levels[cdev->cur_state];
	aspeed_set_pwm_port_fan_ctrl(cdev->priv, cdev->pwm_port,
				     cdev->cooling_levels[cdev->cur_state]);

	return 0;
}