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
struct ingenic_clk {size_t idx; struct ingenic_cgu* cgu; } ;
struct ingenic_cgu_clk_info {scalar_t__ type; } ;
struct ingenic_cgu {struct ingenic_cgu_clk_info* clock_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CGU_CLK_PLL ; 

__attribute__((used)) static inline const struct ingenic_cgu_clk_info *to_clk_info(
		struct ingenic_clk *ingenic_clk)
{
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info;

	clk_info = &cgu->clock_info[ingenic_clk->idx];
	BUG_ON(clk_info->type != CGU_CLK_PLL);

	return clk_info;
}