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
 int /*<<< orphan*/  VALIDATE_DESC_VOID (struct gpio_desc*) ; 
 int /*<<< orphan*/  extra_checks ; 
 int /*<<< orphan*/  gpiod_set_value_nocheck (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 

void gpiod_set_value_cansleep(struct gpio_desc *desc, int value)
{
	might_sleep_if(extra_checks);
	VALIDATE_DESC_VOID(desc);
	gpiod_set_value_nocheck(desc, value);
}