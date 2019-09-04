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
struct sii8620 {int /*<<< orphan*/  supplies; int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  clk_xtal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sii8620_hw_off(struct sii8620 *ctx)
{
	clk_disable_unprepare(ctx->clk_xtal);
	gpiod_set_value(ctx->gpio_reset, 1);
	return regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
}