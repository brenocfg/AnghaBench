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
struct timer_list {int dummy; } ;
struct pps_gpio_device_data {int /*<<< orphan*/  echo_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  echo_timer ; 
 struct pps_gpio_device_data* from_timer (struct pps_gpio_device_data const*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pps_gpio_echo_timer_callback(struct timer_list *t)
{
	const struct pps_gpio_device_data *info;

	info = from_timer(info, t, echo_timer);

	gpiod_set_value(info->echo_pin, 0);
}