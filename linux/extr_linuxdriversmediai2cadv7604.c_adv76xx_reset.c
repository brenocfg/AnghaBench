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
struct adv76xx_state {scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void adv76xx_reset(struct adv76xx_state *state)
{
	if (state->reset_gpio) {
		/* ADV76XX can be reset by a low reset pulse of minimum 5 ms. */
		gpiod_set_value_cansleep(state->reset_gpio, 0);
		usleep_range(5000, 10000);
		gpiod_set_value_cansleep(state->reset_gpio, 1);
		/* It is recommended to wait 5 ms after the low pulse before */
		/* an I2C write is performed to the ADV76XX. */
		usleep_range(5000, 10000);
	}
}