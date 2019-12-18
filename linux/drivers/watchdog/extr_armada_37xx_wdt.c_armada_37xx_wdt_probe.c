#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct regmap {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_15__ {int min_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  status; TYPE_5__* parent; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct armada_37xx_watchdog {TYPE_1__ wdt; int /*<<< orphan*/  clk_rate; struct regmap* clk; int /*<<< orphan*/  reg; struct regmap* cpu_misc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  armada_37xx_wdt_info ; 
 scalar_t__ armada_37xx_wdt_is_running (struct armada_37xx_watchdog*) ; 
 int /*<<< orphan*/  armada_37xx_wdt_ops ; 
 int /*<<< orphan*/  armada_37xx_wdt_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_clk_disable_unprepare ; 
 int /*<<< orphan*/  clk_get_rate (struct regmap*) ; 
 int clk_prepare_enable (struct regmap*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int /*<<< orphan*/ ,char*) ; 
 int devm_add_action_or_reset (TYPE_5__*,int /*<<< orphan*/ ,struct regmap*) ; 
 struct regmap* devm_clk_get (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct armada_37xx_watchdog* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct armada_37xx_watchdog*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int armada_37xx_wdt_probe(struct platform_device *pdev)
{
	struct armada_37xx_watchdog *dev;
	struct resource *res;
	struct regmap *regmap;
	int ret;

	dev = devm_kzalloc(&pdev->dev, sizeof(struct armada_37xx_watchdog),
			   GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->wdt.info = &armada_37xx_wdt_info;
	dev->wdt.ops = &armada_37xx_wdt_ops;

	regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						 "marvell,system-controller");
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);
	dev->cpu_misc = regmap;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	dev->reg = devm_ioremap(&pdev->dev, res->start, resource_size(res));

	/* init clock */
	dev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dev->clk))
		return PTR_ERR(dev->clk);

	ret = clk_prepare_enable(dev->clk);
	if (ret)
		return ret;
	ret = devm_add_action_or_reset(&pdev->dev,
				       armada_clk_disable_unprepare, dev->clk);
	if (ret)
		return ret;

	dev->clk_rate = clk_get_rate(dev->clk);
	if (!dev->clk_rate)
		return -EINVAL;

	/*
	 * Since the timeout in seconds is given as 32 bit unsigned int, and
	 * the counters hold 64 bit values, even after multiplication by clock
	 * rate the counter can hold timeout of UINT_MAX seconds.
	 */
	dev->wdt.min_timeout = 1;
	dev->wdt.max_timeout = UINT_MAX;
	dev->wdt.parent = &pdev->dev;

	/* default value, possibly override by module parameter or dtb */
	dev->wdt.timeout = WATCHDOG_TIMEOUT;
	watchdog_init_timeout(&dev->wdt, timeout, &pdev->dev);

	platform_set_drvdata(pdev, &dev->wdt);
	watchdog_set_drvdata(&dev->wdt, dev);

	armada_37xx_wdt_set_timeout(&dev->wdt, dev->wdt.timeout);

	if (armada_37xx_wdt_is_running(dev))
		set_bit(WDOG_HW_RUNNING, &dev->wdt.status);

	watchdog_set_nowayout(&dev->wdt, nowayout);
	watchdog_stop_on_reboot(&dev->wdt);
	ret = devm_watchdog_register_device(&pdev->dev, &dev->wdt);
	if (ret)
		return ret;

	dev_info(&pdev->dev, "Initial timeout %d sec%s\n",
		 dev->wdt.timeout, nowayout ? ", nowayout" : "");

	return 0;
}