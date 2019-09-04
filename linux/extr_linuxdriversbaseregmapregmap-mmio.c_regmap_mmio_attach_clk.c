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
struct regmap_mmio_context {int attached_clk; struct clk* clk; } ;
struct regmap {struct regmap_mmio_context* bus_context; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int clk_prepare (struct clk*) ; 

int regmap_mmio_attach_clk(struct regmap *map, struct clk *clk)
{
	struct regmap_mmio_context *ctx = map->bus_context;

	ctx->clk = clk;
	ctx->attached_clk = true;

	return clk_prepare(ctx->clk);
}