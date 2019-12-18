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
struct watchdog_device {int dummy; } ;
struct mlxreg_wdt {size_t ping_idx; int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct mlxreg_core_data {int /*<<< orphan*/  bit; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {struct mlxreg_core_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int regmap_update_bits_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 struct mlxreg_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int mlxreg_wdt_ping(struct watchdog_device *wdd)
{
	struct mlxreg_wdt *wdt = watchdog_get_drvdata(wdd);
	struct mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->ping_idx];

	return regmap_update_bits_base(wdt->regmap, reg_data->reg,
				       ~reg_data->mask, BIT(reg_data->bit),
				       NULL, false, true);
}