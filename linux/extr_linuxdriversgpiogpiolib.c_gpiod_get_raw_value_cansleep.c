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
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc const*) ; 
 int /*<<< orphan*/  extra_checks ; 
 int gpiod_get_raw_value_commit (struct gpio_desc const*) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 

int gpiod_get_raw_value_cansleep(const struct gpio_desc *desc)
{
	might_sleep_if(extra_checks);
	VALIDATE_DESC(desc);
	return gpiod_get_raw_value_commit(desc);
}