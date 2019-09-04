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
struct cam_clk_provider {unsigned int num_clocks; int /*<<< orphan*/ * clks; scalar_t__ of_node; } ;
struct fimc_md {struct cam_clk_provider clk_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (scalar_t__) ; 

__attribute__((used)) static void fimc_md_unregister_clk_provider(struct fimc_md *fmd)
{
	struct cam_clk_provider *cp = &fmd->clk_provider;
	unsigned int i;

	if (cp->of_node)
		of_clk_del_provider(cp->of_node);

	for (i = 0; i < cp->num_clocks; i++)
		clk_unregister(cp->clks[i]);
}