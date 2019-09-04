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
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_clks_enable(struct venus_core *core)
{
	const struct venus_resources *res = core->res;
	unsigned int i;
	int ret;

	for (i = 0; i < res->clks_num; i++) {
		ret = clk_prepare_enable(core->clks[i]);
		if (ret)
			goto err;
	}

	return 0;
err:
	while (i--)
		clk_disable_unprepare(core->clks[i]);

	return ret;
}