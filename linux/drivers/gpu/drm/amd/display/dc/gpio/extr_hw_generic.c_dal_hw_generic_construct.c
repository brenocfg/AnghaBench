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
typedef  int /*<<< orphan*/  uint32_t ;
struct hw_generic {int /*<<< orphan*/  base; } ;
struct dc_context {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  dal_hw_gpio_construct (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dc_context*) ; 

__attribute__((used)) static void dal_hw_generic_construct(
	struct hw_generic *pin,
	enum gpio_id id,
	uint32_t en,
	struct dc_context *ctx)
{
	dal_hw_gpio_construct(&pin->base, id, en, ctx);
}