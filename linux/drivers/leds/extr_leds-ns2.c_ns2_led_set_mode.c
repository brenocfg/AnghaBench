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
struct ns2_led_data {int num_modes; int /*<<< orphan*/  rw_lock; TYPE_1__* modval; int /*<<< orphan*/  slow; int /*<<< orphan*/  cmd; int /*<<< orphan*/  can_sleep; } ;
typedef  enum ns2_led_modes { ____Placeholder_ns2_led_modes } ns2_led_modes ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  slow_level; int /*<<< orphan*/  cmd_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ns2_led_set_mode(struct ns2_led_data *led_dat,
			     enum ns2_led_modes mode)
{
	int i;
	bool found = false;
	unsigned long flags;

	for (i = 0; i < led_dat->num_modes; i++)
		if (mode == led_dat->modval[i].mode) {
			found = true;
			break;
		}

	if (!found)
		return;

	write_lock_irqsave(&led_dat->rw_lock, flags);

	if (!led_dat->can_sleep) {
		gpio_set_value(led_dat->cmd,
			       led_dat->modval[i].cmd_level);
		gpio_set_value(led_dat->slow,
			       led_dat->modval[i].slow_level);
		goto exit_unlock;
	}

	gpio_set_value_cansleep(led_dat->cmd, led_dat->modval[i].cmd_level);
	gpio_set_value_cansleep(led_dat->slow, led_dat->modval[i].slow_level);

exit_unlock:
	write_unlock_irqrestore(&led_dat->rw_lock, flags);
}