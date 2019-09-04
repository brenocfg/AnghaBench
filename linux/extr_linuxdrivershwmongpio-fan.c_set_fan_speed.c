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
struct gpio_fan_data {int speed_index; TYPE_1__* speed; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_fan_ctrl (struct gpio_fan_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_fan_speed(struct gpio_fan_data *fan_data, int speed_index)
{
	if (fan_data->speed_index == speed_index)
		return;

	__set_fan_ctrl(fan_data, fan_data->speed[speed_index].ctrl_val);
	fan_data->speed_index = speed_index;
}