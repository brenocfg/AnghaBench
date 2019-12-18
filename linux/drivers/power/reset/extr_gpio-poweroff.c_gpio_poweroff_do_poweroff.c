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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  active_delay ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inactive_delay ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_gpio ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void gpio_poweroff_do_poweroff(void)
{
	BUG_ON(!reset_gpio);

	/* drive it active, also inactive->active edge */
	gpiod_direction_output(reset_gpio, 1);
	mdelay(active_delay);

	/* drive inactive, also active->inactive edge */
	gpiod_set_value_cansleep(reset_gpio, 0);
	mdelay(inactive_delay);

	/* drive it active, also inactive->active edge */
	gpiod_set_value_cansleep(reset_gpio, 1);

	/* give it some time */
	mdelay(timeout);

	WARN_ON(1);
}