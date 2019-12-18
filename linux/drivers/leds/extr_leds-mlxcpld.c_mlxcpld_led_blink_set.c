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
struct TYPE_2__ {scalar_t__ base_color; int /*<<< orphan*/  offset; int /*<<< orphan*/  mask; } ;
struct mlxcpld_led_priv {TYPE_1__ param; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MLXCPLD_LED_BLINK_3HZ ; 
 unsigned long MLXCPLD_LED_BLINK_6HZ ; 
 scalar_t__ MLXCPLD_LED_OFFSET_FULL ; 
 scalar_t__ MLXCPLD_LED_OFFSET_HALF ; 
 struct mlxcpld_led_priv* cdev_to_priv (struct led_classdev*) ; 
 int /*<<< orphan*/  mlxcpld_led_store_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mlxcpld_led_blink_set(struct led_classdev *led,
				 unsigned long *delay_on,
				 unsigned long *delay_off)
{
	struct mlxcpld_led_priv *pled = cdev_to_priv(led);

	/*
	 * HW supports two types of blinking: full (6Hz) and half (3Hz).
	 * For delay on/off zero default setting 3Hz is used.
	 */
	if (!(*delay_on == 0 && *delay_off == 0) &&
	    !(*delay_on == MLXCPLD_LED_BLINK_3HZ &&
	      *delay_off == MLXCPLD_LED_BLINK_3HZ) &&
	    !(*delay_on == MLXCPLD_LED_BLINK_6HZ &&
	      *delay_off == MLXCPLD_LED_BLINK_6HZ))
		return -EINVAL;

	if (*delay_on == MLXCPLD_LED_BLINK_6HZ)
		mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
				     pled->param.base_color +
				     MLXCPLD_LED_OFFSET_FULL);
	else
		mlxcpld_led_store_hw(pled->param.mask, pled->param.offset,
				     pled->param.base_color +
				     MLXCPLD_LED_OFFSET_HALF);

	return 0;
}