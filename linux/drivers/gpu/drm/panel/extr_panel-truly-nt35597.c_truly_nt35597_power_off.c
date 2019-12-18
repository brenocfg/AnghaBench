#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct truly_nt35597 {int /*<<< orphan*/  dev; TYPE_1__* supplies; int /*<<< orphan*/  reset_gpio; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_disable (int,TYPE_1__*) ; 
 int /*<<< orphan*/ * regulator_disable_loads ; 
 int regulator_set_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int truly_nt35597_power_off(struct truly_nt35597 *ctx)
{
	int ret = 0;
	int i;

	gpiod_set_value(ctx->reset_gpio, 1);

	for (i = 0; i < ARRAY_SIZE(ctx->supplies); i++) {
		ret = regulator_set_load(ctx->supplies[i].consumer,
				regulator_disable_loads[i]);
		if (ret) {
			DRM_DEV_ERROR(ctx->dev,
				"regulator_set_load failed %d\n", ret);
			return ret;
		}
	}

	ret = regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret) {
		DRM_DEV_ERROR(ctx->dev,
			"regulator_bulk_disable failed %d\n", ret);
	}
	return ret;
}