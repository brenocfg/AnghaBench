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
struct gpio {int mode; scalar_t__ pin; int /*<<< orphan*/  en; int /*<<< orphan*/  id; int /*<<< orphan*/  service; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_mode { ____Placeholder_gpio_mode } gpio_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int GPIO_RESULT_ALREADY_OPENED ; 
 int dal_gpio_service_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

enum gpio_result dal_gpio_open_ex(
	struct gpio *gpio,
	enum gpio_mode mode)
{
	if (gpio->pin) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_ALREADY_OPENED;
	}

	gpio->mode = mode;

	return dal_gpio_service_open(
		gpio->service, gpio->id, gpio->en, mode, &gpio->pin);
}