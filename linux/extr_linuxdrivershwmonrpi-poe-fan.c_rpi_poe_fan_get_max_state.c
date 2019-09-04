#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thermal_cooling_device {struct rpi_poe_fan_ctx* devdata; } ;
struct rpi_poe_fan_ctx {unsigned long rpi_poe_fan_max_state; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int rpi_poe_fan_get_max_state(struct thermal_cooling_device *cdev,
				     unsigned long *state)
{
	struct rpi_poe_fan_ctx *ctx = cdev->devdata;

	if (!ctx)
		return -EINVAL;

	*state = ctx->rpi_poe_fan_max_state;

	return 0;
}