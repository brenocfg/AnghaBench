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
typedef  int /*<<< orphan*/  uint32_t ;
struct hw_gpio_pin {int dummy; } ;
struct TYPE_2__ {struct hw_gpio_pin base; } ;
struct hw_ddc {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIO_DDC_LINE_MAX ; 
 int /*<<< orphan*/  GPIO_DDC_LINE_MIN ; 
 int /*<<< orphan*/  construct (struct hw_ddc*,int,int /*<<< orphan*/ ,struct dc_context*) ; 
 struct hw_ddc* kzalloc (int,int /*<<< orphan*/ ) ; 

struct hw_gpio_pin *dal_hw_ddc_create(
	struct dc_context *ctx,
	enum gpio_id id,
	uint32_t en)
{
	struct hw_ddc *pin;

	if ((en < GPIO_DDC_LINE_MIN) || (en > GPIO_DDC_LINE_MAX)) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	pin = kzalloc(sizeof(struct hw_ddc), GFP_KERNEL);
	if (!pin) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	construct(pin, id, en, ctx);
	return &pin->base.base;
}