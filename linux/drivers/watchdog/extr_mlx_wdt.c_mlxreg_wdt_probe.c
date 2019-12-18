#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; struct device* parent; } ;
struct mlxreg_wdt {TYPE_1__ wdd; int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_platform_data {int features; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXREG_CORE_WD_FEATURE_NOWAYOUT ; 
 int MLXREG_CORE_WD_FEATURE_START_AT_BOOT ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct mlxreg_core_platform_data* dev_get_platdata (struct device*) ; 
 struct mlxreg_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlxreg_wdt_check_card_reset (struct mlxreg_wdt*) ; 
 int /*<<< orphan*/  mlxreg_wdt_config (struct mlxreg_wdt*,struct mlxreg_core_platform_data*) ; 
 int mlxreg_wdt_init_timeout (struct mlxreg_wdt*,struct mlxreg_core_platform_data*) ; 
 int mlxreg_wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct mlxreg_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 

__attribute__((used)) static int mlxreg_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mlxreg_core_platform_data *pdata;
	struct mlxreg_wdt *wdt;
	int rc;

	pdata = dev_get_platdata(dev);
	if (!pdata) {
		dev_err(dev, "Failed to get platform data.\n");
		return -EINVAL;
	}
	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->wdd.parent = dev;
	wdt->regmap = pdata->regmap;
	mlxreg_wdt_config(wdt, pdata);

	if ((pdata->features & MLXREG_CORE_WD_FEATURE_NOWAYOUT))
		watchdog_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchdog_stop_on_reboot(&wdt->wdd);
	watchdog_stop_on_unregister(&wdt->wdd);
	watchdog_set_drvdata(&wdt->wdd, wdt);
	rc = mlxreg_wdt_init_timeout(wdt, pdata);
	if (rc)
		goto register_error;

	if ((pdata->features & MLXREG_CORE_WD_FEATURE_START_AT_BOOT)) {
		rc = mlxreg_wdt_start(&wdt->wdd);
		if (rc)
			goto register_error;
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	}
	mlxreg_wdt_check_card_reset(wdt);
	rc = devm_watchdog_register_device(dev, &wdt->wdd);

register_error:
	if (rc)
		dev_err(dev, "Cannot register watchdog device (err=%d)\n", rc);
	return rc;
}