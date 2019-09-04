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
struct ddc {int /*<<< orphan*/  pin_data; int /*<<< orphan*/  pin_clock; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_mode { ____Placeholder_gpio_mode } gpio_mode ;

/* Variables and functions */
 int GPIO_RESULT_OK ; 
 int dal_gpio_change_mode (int /*<<< orphan*/ ,int) ; 
 int dal_gpio_get_mode (int /*<<< orphan*/ ) ; 

enum gpio_result dal_ddc_change_mode(
	struct ddc *ddc,
	enum gpio_mode mode)
{
	enum gpio_result result;

	enum gpio_mode original_mode =
		dal_gpio_get_mode(ddc->pin_data);

	result = dal_gpio_change_mode(ddc->pin_data, mode);

	/* [anaumov] DAL2 code returns GPIO_RESULT_NON_SPECIFIC_ERROR
	 * in case of failures;
	 * set_mode() is so that, in case of failure,
	 * we must explicitly set original mode */

	if (result != GPIO_RESULT_OK)
		goto failure;

	result = dal_gpio_change_mode(ddc->pin_clock, mode);

	if (result == GPIO_RESULT_OK)
		return result;

	dal_gpio_change_mode(ddc->pin_clock, original_mode);

failure:
	dal_gpio_change_mode(ddc->pin_data, original_mode);

	return result;
}