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
struct gpio_desc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ACTIVE_LOW ; 
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc const*) ; 
 int /*<<< orphan*/  extra_checks ; 
 int gpiod_get_raw_value_commit (struct gpio_desc const*) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int gpiod_get_value_cansleep(const struct gpio_desc *desc)
{
	int value;

	might_sleep_if(extra_checks);
	VALIDATE_DESC(desc);
	value = gpiod_get_raw_value_commit(desc);
	if (value < 0)
		return value;

	if (test_bit(FLAG_ACTIVE_LOW, &desc->flags))
		value = !value;

	return value;
}