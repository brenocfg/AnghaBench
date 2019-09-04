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
struct adv7180_state {int /*<<< orphan*/  pwdn_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void adv7180_set_power_pin(struct adv7180_state *state, bool on)
{
	if (!state->pwdn_gpio)
		return;

	if (on) {
		gpiod_set_value_cansleep(state->pwdn_gpio, 0);
		usleep_range(5000, 10000);
	} else {
		gpiod_set_value_cansleep(state->pwdn_gpio, 1);
	}
}