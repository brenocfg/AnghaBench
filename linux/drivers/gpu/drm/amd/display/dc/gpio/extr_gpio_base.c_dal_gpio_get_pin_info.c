#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gpio_pin_info {int dummy; } ;
struct gpio {int /*<<< orphan*/  en; int /*<<< orphan*/  id; TYPE_3__* service; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ translate; } ;
struct TYPE_4__ {scalar_t__ (* id_to_offset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_pin_info*) ;} ;

/* Variables and functions */
 int GPIO_RESULT_INVALID_DATA ; 
 int GPIO_RESULT_OK ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_pin_info*) ; 

enum gpio_result dal_gpio_get_pin_info(
	const struct gpio *gpio,
	struct gpio_pin_info *pin_info)
{
	return gpio->service->translate.funcs->id_to_offset(
		gpio->id, gpio->en, pin_info) ?
		GPIO_RESULT_OK : GPIO_RESULT_INVALID_DATA;
}