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
struct gpio {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;
struct TYPE_3__ {int /*<<< orphan*/  (* offset_to_id ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT_STATE_DEFAULT ; 
 struct gpio* dal_gpio_create (struct gpio_service*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

struct gpio *dal_gpio_service_create_generic_mux(
	struct gpio_service *service,
	uint32_t offset,
	uint32_t mask)
{
	enum gpio_id id;
	uint32_t en;
	struct gpio *generic;

	if (!service->translate.funcs->offset_to_id(offset, mask, &id, &en)) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	generic = dal_gpio_create(
		service, id, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	return generic;
}