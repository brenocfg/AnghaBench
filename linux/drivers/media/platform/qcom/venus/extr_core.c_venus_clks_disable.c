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
struct venus_resources {unsigned int clks_num; } ;
struct venus_core {int /*<<< orphan*/ * clks; struct venus_resources* res; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venus_clks_disable(struct venus_core *core)
{
	const struct venus_resources *res = core->res;
	unsigned int i = res->clks_num;

	while (i--)
		clk_disable_unprepare(core->clks[i]);
}