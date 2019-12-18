#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct stpmic1_wdt {struct stpmic1* pmic; TYPE_1__ wdtdev; } ;
struct stpmic1 {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PMIC_WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  PMIC_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  PMIC_WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct stpmic1* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct stpmic1_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pmic_watchdog_info ; 
 int /*<<< orphan*/  pmic_watchdog_ops ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct stpmic1_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmic_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int ret;
	struct stpmic1 *pmic;
	struct stpmic1_wdt *wdt;

	if (!dev->parent)
		return -EINVAL;

	pmic = dev_get_drvdata(dev->parent);
	if (!pmic)
		return -EINVAL;

	wdt = devm_kzalloc(dev, sizeof(struct stpmic1_wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->pmic = pmic;

	wdt->wdtdev.info = &pmic_watchdog_info;
	wdt->wdtdev.ops = &pmic_watchdog_ops;
	wdt->wdtdev.min_timeout = PMIC_WDT_MIN_TIMEOUT;
	wdt->wdtdev.max_timeout = PMIC_WDT_MAX_TIMEOUT;
	wdt->wdtdev.parent = dev;

	wdt->wdtdev.timeout = PMIC_WDT_DEFAULT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdtdev, 0, dev);

	watchdog_set_nowayout(&wdt->wdtdev, nowayout);
	watchdog_set_drvdata(&wdt->wdtdev, wdt);

	ret = devm_watchdog_register_device(dev, &wdt->wdtdev);
	if (ret)
		return ret;

	dev_dbg(wdt->pmic->dev, "PMIC Watchdog driver probed\n");
	return 0;
}