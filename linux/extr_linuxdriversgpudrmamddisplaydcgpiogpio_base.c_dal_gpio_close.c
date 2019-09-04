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
struct gpio {int /*<<< orphan*/  mode; int /*<<< orphan*/  pin; int /*<<< orphan*/  service; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dal_gpio_service_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dal_gpio_close(
	struct gpio *gpio)
{
	if (!gpio)
		return;

	dal_gpio_service_close(gpio->service, &gpio->pin);

	gpio->mode = GPIO_MODE_UNKNOWN;
}