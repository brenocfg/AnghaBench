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
struct TYPE_3__ {scalar_t__ mux; scalar_t__ en; scalar_t__ a; scalar_t__ mask; } ;
struct TYPE_4__ {int id; int opened; int /*<<< orphan*/  mode; int /*<<< orphan*/  en; struct dc_context* ctx; } ;
struct hw_gpio {int mux_supported; TYPE_1__ store; TYPE_2__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MODE_UNKNOWN ; 

void dal_hw_gpio_construct(
	struct hw_gpio *pin,
	enum gpio_id id,
	uint32_t en,
	struct dc_context *ctx)
{
	pin->base.ctx = ctx;
	pin->base.id = id;
	pin->base.en = en;
	pin->base.mode = GPIO_MODE_UNKNOWN;
	pin->base.opened = false;

	pin->store.mask = 0;
	pin->store.a = 0;
	pin->store.en = 0;
	pin->store.mux = 0;

	pin->mux_supported = false;
}