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
struct gpio_config_data {int dummy; } ;
struct gpio {TYPE_2__* pin; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* set_config ) (TYPE_2__*,struct gpio_config_data const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int GPIO_RESULT_NULL_HANDLE ; 
 int stub1 (TYPE_2__*,struct gpio_config_data const*) ; 

enum gpio_result dal_gpio_set_config(
	struct gpio *gpio,
	const struct gpio_config_data *config_data)
{
	if (!gpio->pin) {
		BREAK_TO_DEBUGGER();
		return GPIO_RESULT_NULL_HANDLE;
	}

	return gpio->pin->funcs->set_config(gpio->pin, config_data);
}