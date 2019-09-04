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
struct TYPE_2__ {unsigned int clk_num; int /*<<< orphan*/ * clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,int /*<<< orphan*/ ) ; 

void pistachio_clk_register_provider(struct pistachio_clk_provider *p)
{
	unsigned int i;

	for (i = 0; i < p->clk_data.clk_num; i++) {
		if (IS_ERR(p->clk_data.clks[i]))
			pr_warn("Failed to register clock %d: %ld\n", i,
				PTR_ERR(p->clk_data.clks[i]));
	}

	of_clk_add_provider(p->node, of_clk_src_onecell_get, &p->clk_data);
}