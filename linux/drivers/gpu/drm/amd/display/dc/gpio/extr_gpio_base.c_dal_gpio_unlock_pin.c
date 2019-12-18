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
struct gpio {int /*<<< orphan*/  en; int /*<<< orphan*/  id; int /*<<< orphan*/  service; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;

/* Variables and functions */
 int dal_gpio_service_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum gpio_result dal_gpio_unlock_pin(
	struct gpio *gpio)
{
	return dal_gpio_service_unlock(gpio->service, gpio->id, gpio->en);
}