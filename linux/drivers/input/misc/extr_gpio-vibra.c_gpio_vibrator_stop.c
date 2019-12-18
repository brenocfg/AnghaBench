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
struct gpio_vibrator {int vcc_on; int /*<<< orphan*/  vcc; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_vibrator_stop(struct gpio_vibrator *vibrator)
{
	gpiod_set_value_cansleep(vibrator->gpio, 0);

	if (vibrator->vcc_on) {
		regulator_disable(vibrator->vcc);
		vibrator->vcc_on = false;
	}
}