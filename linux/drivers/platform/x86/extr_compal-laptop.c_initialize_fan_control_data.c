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
struct compal_data {int pwm_enable; int curr_pwm; } ;

/* Variables and functions */

__attribute__((used)) static void initialize_fan_control_data(struct compal_data *data)
{
	data->pwm_enable = 2; /* Keep motherboard in control for now */
	data->curr_pwm = 255; /* Try not to cause a CPU_on_fire exception
				 if we take over... */
}