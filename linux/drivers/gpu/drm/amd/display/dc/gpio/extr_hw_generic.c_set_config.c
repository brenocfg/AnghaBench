#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw_gpio_pin {int dummy; } ;
struct hw_generic {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mux_select; int /*<<< orphan*/  enable_output_from_mux; } ;
struct TYPE_4__ {TYPE_1__ generic_mux; } ;
struct gpio_config_data {TYPE_2__ config; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_EN ; 
 int /*<<< orphan*/  GENERIC_SEL ; 
 int GPIO_RESULT_INVALID_DATA ; 
 int GPIO_RESULT_OK ; 
 struct hw_generic* HW_GENERIC_FROM_BASE (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mux ; 

__attribute__((used)) static enum gpio_result set_config(
	struct hw_gpio_pin *ptr,
	const struct gpio_config_data *config_data)
{
	struct hw_generic *generic = HW_GENERIC_FROM_BASE(ptr);

	if (!config_data)
		return GPIO_RESULT_INVALID_DATA;

	REG_UPDATE_2(mux,
		GENERIC_EN, config_data->config.generic_mux.enable_output_from_mux,
		GENERIC_SEL, config_data->config.generic_mux.mux_select);

	return GPIO_RESULT_OK;
}