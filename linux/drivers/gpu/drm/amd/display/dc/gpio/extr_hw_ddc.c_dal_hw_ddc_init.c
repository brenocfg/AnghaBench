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
typedef  scalar_t__ uint32_t ;
struct hw_ddc {int dummy; } ;
struct dc_context {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPIO_DDC_LINE_MAX ; 
 scalar_t__ GPIO_DDC_LINE_MIN ; 
 int /*<<< orphan*/  construct (struct hw_ddc*,int,scalar_t__,struct dc_context*) ; 
 struct hw_ddc* kzalloc (int,int /*<<< orphan*/ ) ; 

void dal_hw_ddc_init(
	struct hw_ddc **hw_ddc,
	struct dc_context *ctx,
	enum gpio_id id,
	uint32_t en)
{
	if ((en < GPIO_DDC_LINE_MIN) || (en > GPIO_DDC_LINE_MAX)) {
		ASSERT_CRITICAL(false);
		*hw_ddc = NULL;
	}

	*hw_ddc = kzalloc(sizeof(struct hw_ddc), GFP_KERNEL);
	if (!*hw_ddc) {
		ASSERT_CRITICAL(false);
		return;
	}

	construct(*hw_ddc, id, en, ctx);
}