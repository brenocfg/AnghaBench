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
struct hw_gpio_pin {TYPE_1__* funcs; int /*<<< orphan*/  en; int /*<<< orphan*/  id; } ;
struct gpio_service {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hw_gpio_pin*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  set_pin_free (struct gpio_service*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hw_gpio_pin*) ; 

void dal_gpio_service_close(
	struct gpio_service *service,
	struct hw_gpio_pin **ptr)
{
	struct hw_gpio_pin *pin;

	if (!ptr) {
		ASSERT_CRITICAL(false);
		return;
	}

	pin = *ptr;

	if (pin) {
		set_pin_free(service, pin->id, pin->en);

		pin->funcs->close(pin);

		*ptr = NULL;
	}
}