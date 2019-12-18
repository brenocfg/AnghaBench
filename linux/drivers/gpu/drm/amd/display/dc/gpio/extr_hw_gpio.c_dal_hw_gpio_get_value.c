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
typedef  int /*<<< orphan*/  uint32_t ;
struct hw_gpio_pin {int mode; } ;
struct hw_gpio {int dummy; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 struct hw_gpio* FROM_HW_GPIO_PIN (struct hw_gpio_pin const*) ; 
#define  GPIO_MODE_FAST_OUTPUT 131 
#define  GPIO_MODE_HARDWARE 130 
#define  GPIO_MODE_INPUT 129 
#define  GPIO_MODE_OUTPUT 128 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_OK ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Y ; 
 int /*<<< orphan*/  Y_reg ; 

enum gpio_result dal_hw_gpio_get_value(
	const struct hw_gpio_pin *ptr,
	uint32_t *value)
{
	const struct hw_gpio *gpio = FROM_HW_GPIO_PIN(ptr);

	enum gpio_result result = GPIO_RESULT_OK;

	switch (ptr->mode) {
	case GPIO_MODE_INPUT:
	case GPIO_MODE_OUTPUT:
	case GPIO_MODE_HARDWARE:
	case GPIO_MODE_FAST_OUTPUT:
		REG_GET(Y_reg, Y, value);
		break;
	default:
		result = GPIO_RESULT_NON_SPECIFIC_ERROR;
	}

	return result;
}