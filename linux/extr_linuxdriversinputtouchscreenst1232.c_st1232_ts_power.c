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
struct st1232_ts_data {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st1232_ts_power(struct st1232_ts_data *ts, bool poweron)
{
	if (gpio_is_valid(ts->reset_gpio))
		gpio_direction_output(ts->reset_gpio, poweron);
}