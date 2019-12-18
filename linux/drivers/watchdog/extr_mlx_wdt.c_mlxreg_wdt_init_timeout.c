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
typedef  int /*<<< orphan*/  u32 ;
struct mlxreg_wdt {size_t timeout_idx; int /*<<< orphan*/  wdd; } ;
struct mlxreg_core_platform_data {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  health_cntr; } ;

/* Variables and functions */
 int mlxreg_wdt_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxreg_wdt_init_timeout(struct mlxreg_wdt *wdt,
				   struct mlxreg_core_platform_data *pdata)
{
	u32 timeout;

	timeout = pdata->data[wdt->timeout_idx].health_cntr;
	return mlxreg_wdt_set_timeout(&wdt->wdd, timeout);
}