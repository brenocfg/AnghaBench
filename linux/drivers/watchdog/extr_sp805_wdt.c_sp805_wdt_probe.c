#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  status; int /*<<< orphan*/  timeout; TYPE_9__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct sp805_wdt {TYPE_1__ wdd; int /*<<< orphan*/  lock; struct amba_device* adev; int /*<<< orphan*/  rate; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct amba_id {int dummy; } ;
struct TYPE_18__ {scalar_t__ of_node; } ;
struct amba_device {TYPE_9__ dev; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,struct sp805_wdt*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  device_property_read_u64 (TYPE_9__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_9__*,int /*<<< orphan*/ *) ; 
 struct sp805_wdt* devm_kzalloc (TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_acpi_companion (TYPE_9__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct sp805_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wdt_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  wdt_info ; 
 scalar_t__ wdt_is_running (TYPE_1__*) ; 
 int /*<<< orphan*/  wdt_ops ; 
 int /*<<< orphan*/  wdt_setload (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sp805_wdt_probe(struct amba_device *adev, const struct amba_id *id)
{
	struct sp805_wdt *wdt;
	int ret = 0;

	wdt = devm_kzalloc(&adev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt) {
		ret = -ENOMEM;
		goto err;
	}

	wdt->base = devm_ioremap_resource(&adev->dev, &adev->res);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	if (adev->dev.of_node) {
		wdt->clk = devm_clk_get(&adev->dev, NULL);
		if (IS_ERR(wdt->clk)) {
			dev_err(&adev->dev, "Clock not found\n");
			return PTR_ERR(wdt->clk);
		}
		wdt->rate = clk_get_rate(wdt->clk);
	} else if (has_acpi_companion(&adev->dev)) {
		/*
		 * When Driver probe with ACPI device, clock devices
		 * are not available, so watchdog rate get from
		 * clock-frequency property given in _DSD object.
		 */
		device_property_read_u64(&adev->dev, "clock-frequency",
					 &wdt->rate);
		if (!wdt->rate) {
			dev_err(&adev->dev, "no clock-frequency property\n");
			return -ENODEV;
		}
	}

	wdt->adev = adev;
	wdt->wdd.info = &wdt_info;
	wdt->wdd.ops = &wdt_ops;
	wdt->wdd.parent = &adev->dev;

	spin_lock_init(&wdt->lock);
	watchdog_set_nowayout(&wdt->wdd, nowayout);
	watchdog_set_drvdata(&wdt->wdd, wdt);
	watchdog_set_restart_priority(&wdt->wdd, 128);

	/*
	 * If 'timeout-sec' devicetree property is specified, use that.
	 * Otherwise, use DEFAULT_TIMEOUT
	 */
	wdt->wdd.timeout = DEFAULT_TIMEOUT;
	watchdog_init_timeout(&wdt->wdd, 0, &adev->dev);
	wdt_setload(&wdt->wdd, wdt->wdd.timeout);

	/*
	 * If HW is already running, enable/reset the wdt and set the running
	 * bit to tell the wdt subsystem
	 */
	if (wdt_is_running(&wdt->wdd)) {
		wdt_enable(&wdt->wdd);
		set_bit(WDOG_HW_RUNNING, &wdt->wdd.status);
	}

	ret = watchdog_register_device(&wdt->wdd);
	if (ret)
		goto err;
	amba_set_drvdata(adev, wdt);

	dev_info(&adev->dev, "registration successful\n");
	return 0;

err:
	dev_err(&adev->dev, "Probe Failed!!!\n");
	return ret;
}