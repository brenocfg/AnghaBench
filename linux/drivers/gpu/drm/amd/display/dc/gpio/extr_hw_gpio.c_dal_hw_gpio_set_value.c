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
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  A_reg ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  EN_reg ; 
 struct hw_gpio* FROM_HW_GPIO_PIN (struct hw_gpio_pin const*) ; 
#define  GPIO_MODE_FAST_OUTPUT 129 
#define  GPIO_MODE_OUTPUT 128 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_OK ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum gpio_result dal_hw_gpio_set_value(
	const struct hw_gpio_pin *ptr,
	uint32_t value)
{
	struct hw_gpio *gpio = FROM_HW_GPIO_PIN(ptr);

	/* This is the public interface
	 * where the input comes from client, not shifted yet
	 * (because client does not know the shifts). */

	switch (ptr->mode) {
	case GPIO_MODE_OUTPUT:
		REG_UPDATE(A_reg, A, value);
		return GPIO_RESULT_OK;
	case GPIO_MODE_FAST_OUTPUT:
		/* We use (EN) to faster switch (used in DDC GPIO).
		 * So (A) is grounded, output is driven by (EN = 0)
		 * to pull the line down (output == 0) and (EN=1)
		 * then output is tri-state */
		REG_UPDATE(EN_reg, EN, ~value);
		return GPIO_RESULT_OK;
	default:
		return GPIO_RESULT_NON_SPECIFIC_ERROR;
	}
}