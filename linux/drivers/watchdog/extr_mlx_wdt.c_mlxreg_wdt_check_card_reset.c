#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int bootstatus; int /*<<< orphan*/  parent; TYPE_2__* info; } ;
struct mlxreg_wdt {size_t reset_idx; TYPE_3__ wdd; int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct mlxreg_core_data {int mask; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {int options; } ;
struct TYPE_4__ {struct mlxreg_core_data* data; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int WDIOF_CARDRESET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void mlxreg_wdt_check_card_reset(struct mlxreg_wdt *wdt)
{
	struct mlxreg_core_data *reg_data;
	u32 regval;
	int rc;

	if (wdt->reset_idx == -EINVAL)
		return;

	if (!(wdt->wdd.info->options & WDIOF_CARDRESET))
		return;

	reg_data = &wdt->pdata->data[wdt->reset_idx];
	rc = regmap_read(wdt->regmap, reg_data->reg, &regval);
	if (!rc) {
		if (regval & ~reg_data->mask) {
			wdt->wdd.bootstatus = WDIOF_CARDRESET;
			dev_info(wdt->wdd.parent,
				 "watchdog previously reset the CPU\n");
		}
	}
}