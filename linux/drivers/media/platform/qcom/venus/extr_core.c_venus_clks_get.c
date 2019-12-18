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
struct venus_resources {unsigned int clks_num; int /*<<< orphan*/ * clks; } ;
struct venus_core {int /*<<< orphan*/ * clks; struct device* dev; struct venus_resources* res; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venus_clks_get(struct venus_core *core)
{
	const struct venus_resources *res = core->res;
	struct device *dev = core->dev;
	unsigned int i;

	for (i = 0; i < res->clks_num; i++) {
		core->clks[i] = devm_clk_get(dev, res->clks[i]);
		if (IS_ERR(core->clks[i]))
			return PTR_ERR(core->clks[i]);
	}

	return 0;
}