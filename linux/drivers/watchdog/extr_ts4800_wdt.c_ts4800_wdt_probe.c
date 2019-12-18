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
struct watchdog_device {scalar_t__ timeout; scalar_t__ max_timeout; scalar_t__ min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct ts4800_wdt {struct watchdog_device wdd; int /*<<< orphan*/  regmap; int /*<<< orphan*/  feed_offset; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ timeout; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 size_t MAX_TIMEOUT_INDEX ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ts4800_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ts4800_wdt*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 
 int /*<<< orphan*/  ts4800_wdt_info ; 
 TYPE_1__* ts4800_wdt_map ; 
 int /*<<< orphan*/  ts4800_wdt_ops ; 
 int /*<<< orphan*/  ts4800_wdt_set_timeout (struct watchdog_device*,scalar_t__) ; 
 int /*<<< orphan*/  ts4800_wdt_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct ts4800_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts4800_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *syscon_np;
	struct watchdog_device *wdd;
	struct ts4800_wdt *wdt;
	u32 reg;
	int ret;

	syscon_np = of_parse_phandle(np, "syscon", 0);
	if (!syscon_np) {
		dev_err(dev, "no syscon property\n");
		return -ENODEV;
	}

	ret = of_property_read_u32_index(np, "syscon", 1, &reg);
	if (ret < 0) {
		dev_err(dev, "no offset in syscon\n");
		return ret;
	}

	/* allocate memory for watchdog struct */
	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	/* set regmap and offset to know where to write */
	wdt->feed_offset = reg;
	wdt->regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);
	if (IS_ERR(wdt->regmap)) {
		dev_err(dev, "cannot get parent's regmap\n");
		return PTR_ERR(wdt->regmap);
	}

	/* Initialize struct watchdog_device */
	wdd = &wdt->wdd;
	wdd->parent = dev;
	wdd->info = &ts4800_wdt_info;
	wdd->ops = &ts4800_wdt_ops;
	wdd->min_timeout = ts4800_wdt_map[0].timeout;
	wdd->max_timeout = ts4800_wdt_map[MAX_TIMEOUT_INDEX].timeout;

	watchdog_set_drvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, 0, dev);

	/*
	 * As this watchdog supports only a few values, ts4800_wdt_set_timeout
	 * must be called to initialize timeout and feed_val with valid values.
	 * Default to maximum timeout if none, or an invalid one, is provided in
	 * device tree.
	 */
	if (!wdd->timeout)
		wdd->timeout = wdd->max_timeout;
	ts4800_wdt_set_timeout(wdd, wdd->timeout);

	/*
	 * The feed register is write-only, so it is not possible to determine
	 * watchdog's state. Disable it to be in a known state.
	 */
	ts4800_wdt_stop(wdd);

	ret = devm_watchdog_register_device(dev, wdd);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, wdt);

	dev_info(dev, "initialized (timeout = %d sec, nowayout = %d)\n",
		 wdd->timeout, nowayout);

	return 0;
}