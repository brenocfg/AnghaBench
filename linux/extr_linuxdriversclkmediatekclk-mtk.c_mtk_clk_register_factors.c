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
struct mtk_fixed_factor {size_t id; int /*<<< orphan*/  name; int /*<<< orphan*/  div; int /*<<< orphan*/  mult; int /*<<< orphan*/  parent_name; } ;
struct clk_onecell_data {struct clk** clks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 struct clk* clk_register_fixed_factor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mtk_clk_register_factors(const struct mtk_fixed_factor *clks,
		int num, struct clk_onecell_data *clk_data)
{
	int i;
	struct clk *clk;

	for (i = 0; i < num; i++) {
		const struct mtk_fixed_factor *ff = &clks[i];

		if (clk_data && !IS_ERR_OR_NULL(clk_data->clks[ff->id]))
			continue;

		clk = clk_register_fixed_factor(NULL, ff->name, ff->parent_name,
				CLK_SET_RATE_PARENT, ff->mult, ff->div);

		if (IS_ERR(clk)) {
			pr_err("Failed to register clk %s: %ld\n",
					ff->name, PTR_ERR(clk));
			continue;
		}

		if (clk_data)
			clk_data->clks[ff->id] = clk;
	}
}