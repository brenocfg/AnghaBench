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
struct ns2_led_data {int num_modes; TYPE_1__* modval; int /*<<< orphan*/  slow; int /*<<< orphan*/  cmd; } ;
typedef  enum ns2_led_modes { ____Placeholder_ns2_led_modes } ns2_led_modes ;
struct TYPE_2__ {int cmd_level; int slow_level; int mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns2_led_get_mode(struct ns2_led_data *led_dat,
			    enum ns2_led_modes *mode)
{
	int i;
	int ret = -EINVAL;
	int cmd_level;
	int slow_level;

	cmd_level = gpio_get_value_cansleep(led_dat->cmd);
	slow_level = gpio_get_value_cansleep(led_dat->slow);

	for (i = 0; i < led_dat->num_modes; i++) {
		if (cmd_level == led_dat->modval[i].cmd_level &&
		    slow_level == led_dat->modval[i].slow_level) {
			*mode = led_dat->modval[i].mode;
			ret = 0;
			break;
		}
	}

	return ret;
}