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
struct hw_gpio_pin {int opened; int /*<<< orphan*/  mode; } ;
struct hw_gpio {int dummy; } ;

/* Variables and functions */
 struct hw_gpio* FROM_HW_GPIO_PIN (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  GPIO_MODE_UNKNOWN ; 
 int /*<<< orphan*/  restore_registers (struct hw_gpio*) ; 

void dal_hw_gpio_close(
	struct hw_gpio_pin *ptr)
{
	struct hw_gpio *pin = FROM_HW_GPIO_PIN(ptr);

	restore_registers(pin);

	ptr->mode = GPIO_MODE_UNKNOWN;
	ptr->opened = false;
}