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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct gpio_service {TYPE_2__ translate; } ;
struct gpio_pin_info {int mask; int offset; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;
struct TYPE_3__ {int /*<<< orphan*/  (* id_to_offset ) (int,int /*<<< orphan*/ ,struct gpio_pin_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,struct gpio_pin_info*) ; 

struct gpio_pin_info dal_gpio_get_generic_pin_info(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en)
{
	struct gpio_pin_info pin;

	if (service->translate.funcs->id_to_offset) {
		service->translate.funcs->id_to_offset(id, en, &pin);
	} else {
		pin.mask = 0xFFFFFFFF;
		pin.offset = 0xFFFFFFFF;
	}

	return pin;
}