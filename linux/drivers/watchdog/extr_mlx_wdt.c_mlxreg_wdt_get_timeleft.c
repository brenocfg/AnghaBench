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
typedef  unsigned int u32 ;
struct watchdog_device {int dummy; } ;
struct mlxreg_wdt {size_t tleft_idx; int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct mlxreg_core_data {int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {struct mlxreg_core_data* data; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct mlxreg_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int mlxreg_wdt_get_timeleft(struct watchdog_device *wdd)
{
	struct mlxreg_wdt *wdt = watchdog_get_drvdata(wdd);
	struct mlxreg_core_data *reg_data = &wdt->pdata->data[wdt->tleft_idx];
	u32 regval;
	int rc;

	rc = regmap_read(wdt->regmap, reg_data->reg, &regval);
	/* Return 0 timeleft in case of failure register read. */
	return rc == 0 ? regval : 0;
}