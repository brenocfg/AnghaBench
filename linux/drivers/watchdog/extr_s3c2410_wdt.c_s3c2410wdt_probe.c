#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int min_timeout; struct device* parent; int /*<<< orphan*/  bootstatus; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_timeout; } ;
struct s3c2410_wdt {scalar_t__ clock; TYPE_1__ wdt_device; scalar_t__ reg_base; scalar_t__ pmureg; TYPE_11__* drv_data; int /*<<< orphan*/  lock; struct device* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_12__ {int quirks; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int QUIRKS_HAVE_PMUREG ; 
 int /*<<< orphan*/  S3C2410_WATCHDOG_DEFAULT_TIME ; 
 scalar_t__ S3C2410_WTCON ; 
 unsigned int S3C2410_WTCON_ENABLE ; 
 unsigned int S3C2410_WTCON_INTEN ; 
 unsigned int S3C2410_WTCON_RSTEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 scalar_t__ devm_clk_get (struct device*,char*) ; 
 struct s3c2410_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s3c2410_wdt*) ; 
 unsigned int readl (scalar_t__) ; 
 TYPE_11__* s3c2410_get_wdt_drv_data (struct platform_device*) ; 
 TYPE_1__ s3c2410_wdd ; 
 int /*<<< orphan*/  s3c2410wdt_cpufreq_deregister (struct s3c2410_wdt*) ; 
 int s3c2410wdt_cpufreq_register (struct s3c2410_wdt*) ; 
 int /*<<< orphan*/  s3c2410wdt_get_bootstatus (struct s3c2410_wdt*) ; 
 int /*<<< orphan*/  s3c2410wdt_irq ; 
 int s3c2410wdt_mask_and_disable_reset (struct s3c2410_wdt*,int) ; 
 int /*<<< orphan*/  s3c2410wdt_max_timeout (scalar_t__) ; 
 int s3c2410wdt_set_heartbeat (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410wdt_start (TYPE_1__*) ; 
 int /*<<< orphan*/  s3c2410wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tmr_atboot ; 
 int /*<<< orphan*/  tmr_margin ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct s3c2410_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static int s3c2410wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct s3c2410_wdt *wdt;
	struct resource *wdt_irq;
	unsigned int wtcon;
	int started = 0;
	int ret;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->dev = dev;
	spin_lock_init(&wdt->lock);
	wdt->wdt_device = s3c2410_wdd;

	wdt->drv_data = s3c2410_get_wdt_drv_data(pdev);
	if (wdt->drv_data->quirks & QUIRKS_HAVE_PMUREG) {
		wdt->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
						"samsung,syscon-phandle");
		if (IS_ERR(wdt->pmureg)) {
			dev_err(dev, "syscon regmap lookup failed.\n");
			return PTR_ERR(wdt->pmureg);
		}
	}

	wdt_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (wdt_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err;
	}

	/* get the memory region for the watchdog timer */
	wdt->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wdt->reg_base)) {
		ret = PTR_ERR(wdt->reg_base);
		goto err;
	}

	wdt->clock = devm_clk_get(dev, "watchdog");
	if (IS_ERR(wdt->clock)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = PTR_ERR(wdt->clock);
		goto err;
	}

	ret = clk_prepare_enable(wdt->clock);
	if (ret < 0) {
		dev_err(dev, "failed to enable clock\n");
		return ret;
	}

	wdt->wdt_device.min_timeout = 1;
	wdt->wdt_device.max_timeout = s3c2410wdt_max_timeout(wdt->clock);

	ret = s3c2410wdt_cpufreq_register(wdt);
	if (ret < 0) {
		dev_err(dev, "failed to register cpufreq\n");
		goto err_clk;
	}

	watchdog_set_drvdata(&wdt->wdt_device, wdt);

	/* see if we can actually set the requested timer margin, and if
	 * not, try the default value */

	watchdog_init_timeout(&wdt->wdt_device, tmr_margin, dev);
	ret = s3c2410wdt_set_heartbeat(&wdt->wdt_device,
					wdt->wdt_device.timeout);
	if (ret) {
		started = s3c2410wdt_set_heartbeat(&wdt->wdt_device,
					S3C2410_WATCHDOG_DEFAULT_TIME);

		if (started == 0)
			dev_info(dev,
				 "tmr_margin value out of range, default %d used\n",
				 S3C2410_WATCHDOG_DEFAULT_TIME);
		else
			dev_info(dev, "default timer value is out of range, cannot start\n");
	}

	ret = devm_request_irq(dev, wdt_irq->start, s3c2410wdt_irq, 0,
				pdev->name, pdev);
	if (ret != 0) {
		dev_err(dev, "failed to install irq (%d)\n", ret);
		goto err_cpufreq;
	}

	watchdog_set_nowayout(&wdt->wdt_device, nowayout);
	watchdog_set_restart_priority(&wdt->wdt_device, 128);

	wdt->wdt_device.bootstatus = s3c2410wdt_get_bootstatus(wdt);
	wdt->wdt_device.parent = dev;

	ret = watchdog_register_device(&wdt->wdt_device);
	if (ret)
		goto err_cpufreq;

	ret = s3c2410wdt_mask_and_disable_reset(wdt, false);
	if (ret < 0)
		goto err_unregister;

	if (tmr_atboot && started == 0) {
		dev_info(dev, "starting watchdog timer\n");
		s3c2410wdt_start(&wdt->wdt_device);
	} else if (!tmr_atboot) {
		/* if we're not enabling the watchdog, then ensure it is
		 * disabled if it has been left running from the bootloader
		 * or other source */

		s3c2410wdt_stop(&wdt->wdt_device);
	}

	platform_set_drvdata(pdev, wdt);

	/* print out a statement of readiness */

	wtcon = readl(wdt->reg_base + S3C2410_WTCON);

	dev_info(dev, "watchdog %sactive, reset %sabled, irq %sabled\n",
		 (wtcon & S3C2410_WTCON_ENABLE) ?  "" : "in",
		 (wtcon & S3C2410_WTCON_RSTEN) ? "en" : "dis",
		 (wtcon & S3C2410_WTCON_INTEN) ? "en" : "dis");

	return 0;

 err_unregister:
	watchdog_unregister_device(&wdt->wdt_device);

 err_cpufreq:
	s3c2410wdt_cpufreq_deregister(wdt);

 err_clk:
	clk_disable_unprepare(wdt->clock);

 err:
	return ret;
}