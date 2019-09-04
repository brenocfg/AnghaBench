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
struct mfd_cell {char* name; } ;
struct intel_lpss {int devid; scalar_t__ type; struct clk* clk; int /*<<< orphan*/  clock; TYPE_1__* info; int /*<<< orphan*/  dev; struct mfd_cell* cell; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  devname ;
struct TYPE_2__ {int /*<<< orphan*/  clk_con_id; int /*<<< orphan*/  clk_rate; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ LPSS_DEV_I2C ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_register_fixed_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_create (struct clk*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int intel_lpss_register_clock_divider (struct intel_lpss*,char*,struct clk**) ; 
 int /*<<< orphan*/  intel_lpss_unregister_clock_tree (struct clk*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int intel_lpss_register_clock(struct intel_lpss *lpss)
{
	const struct mfd_cell *cell = lpss->cell;
	struct clk *clk;
	char devname[24];
	int ret;

	if (!lpss->info->clk_rate)
		return 0;

	/* Root clock */
	clk = clk_register_fixed_rate(NULL, dev_name(lpss->dev), NULL, 0,
				      lpss->info->clk_rate);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	snprintf(devname, sizeof(devname), "%s.%d", cell->name, lpss->devid);

	/*
	 * Support for clock divider only if it has some preset value.
	 * Otherwise we assume that the divider is not used.
	 */
	if (lpss->type != LPSS_DEV_I2C) {
		ret = intel_lpss_register_clock_divider(lpss, devname, &clk);
		if (ret)
			goto err_clk_register;
	}

	ret = -ENOMEM;

	/* Clock for the host controller */
	lpss->clock = clkdev_create(clk, lpss->info->clk_con_id, "%s", devname);
	if (!lpss->clock)
		goto err_clk_register;

	lpss->clk = clk;

	return 0;

err_clk_register:
	intel_lpss_unregister_clock_tree(clk);

	return ret;
}