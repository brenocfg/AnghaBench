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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct hw_ddc {TYPE_2__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  dal_hw_gpio_construct (TYPE_2__*,int,int /*<<< orphan*/ ,struct dc_context*) ; 
 int /*<<< orphan*/  funcs ; 

__attribute__((used)) static void construct(
	struct hw_ddc *ddc,
	enum gpio_id id,
	uint32_t en,
	struct dc_context *ctx)
{
	dal_hw_gpio_construct(&ddc->base, id, en, ctx);
	ddc->base.base.funcs = &funcs;
}