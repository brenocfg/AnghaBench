#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct clk** clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  __clk_get_name (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

void pistachio_clk_force_enable(struct pistachio_clk_provider *p,
				unsigned int *clk_ids, unsigned int num)
{
	unsigned int i;
	int err;

	for (i = 0; i < num; i++) {
		struct clk *clk = p->clk_data.clks[clk_ids[i]];

		if (IS_ERR(clk))
			continue;

		err = clk_prepare_enable(clk);
		if (err)
			pr_err("Failed to enable clock %s: %d\n",
			       __clk_get_name(clk), err);
	}
}