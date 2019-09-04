#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; } ;
struct hw_gpio {TYPE_1__ base; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_mode { ____Placeholder_gpio_mode } gpio_mode ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  A_reg ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  EN_reg ; 
#define  GPIO_MODE_FAST_OUTPUT 132 
#define  GPIO_MODE_HARDWARE 131 
#define  GPIO_MODE_INPUT 130 
#define  GPIO_MODE_INTERRUPT 129 
#define  GPIO_MODE_OUTPUT 128 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_OK ; 
 int /*<<< orphan*/  MASK ; 
 int /*<<< orphan*/  MASK_reg ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

enum gpio_result dal_hw_gpio_config_mode(
	struct hw_gpio *gpio,
	enum gpio_mode mode)
{
	gpio->base.mode = mode;

	switch (mode) {
	case GPIO_MODE_INPUT:
		/* turn off output enable, act as input pin;
		 * program the pin as GPIO, mask out signal driven by HW */
		REG_UPDATE(EN_reg, EN, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		return GPIO_RESULT_OK;
	case GPIO_MODE_OUTPUT:
		/* turn on output enable, act as output pin;
		 * program the pin as GPIO, mask out signal driven by HW */
		REG_UPDATE(A_reg, A, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		return GPIO_RESULT_OK;
	case GPIO_MODE_FAST_OUTPUT:
		/* grounding the A register then use the EN register bit
		 * will have faster effect on the rise time */
		REG_UPDATE(A_reg, A, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		return GPIO_RESULT_OK;
	case GPIO_MODE_HARDWARE:
		/* program the pin as tri-state, pin is driven by HW */
		REG_UPDATE(MASK_reg, MASK, 0);
		return GPIO_RESULT_OK;
	case GPIO_MODE_INTERRUPT:
		/* Interrupt mode supported only by HPD (IrqGpio) pins. */
		REG_UPDATE(MASK_reg, MASK, 0);
		return GPIO_RESULT_OK;
	default:
		return GPIO_RESULT_NON_SPECIFIC_ERROR;
	}
}