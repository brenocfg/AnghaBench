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
struct regmap_mmio_context {int /*<<< orphan*/  clk; int /*<<< orphan*/  attached_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void regmap_mmio_free_context(void *context)
{
	struct regmap_mmio_context *ctx = context;

	if (!IS_ERR(ctx->clk)) {
		clk_unprepare(ctx->clk);
		if (!ctx->attached_clk)
			clk_put(ctx->clk);
	}
	kfree(context);
}