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
struct regmap_mmio_context {int /*<<< orphan*/  clk; int /*<<< orphan*/  (* reg_write ) (struct regmap_mmio_context*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct regmap_mmio_context*,unsigned int,unsigned int) ; 

__attribute__((used)) static int regmap_mmio_write(void *context, unsigned int reg, unsigned int val)
{
	struct regmap_mmio_context *ctx = context;
	int ret;

	if (!IS_ERR(ctx->clk)) {
		ret = clk_enable(ctx->clk);
		if (ret < 0)
			return ret;
	}

	ctx->reg_write(ctx, reg, val);

	if (!IS_ERR(ctx->clk))
		clk_disable(ctx->clk);

	return 0;
}