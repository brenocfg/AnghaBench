#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int min_timeout; int max_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; struct device* parent; } ;
struct tqmx86_wdt {TYPE_1__ wdd; int /*<<< orphan*/  io_base; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDT_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioport_map (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tqmx86_wdt* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  tqmx86_wdt_info ; 
 int /*<<< orphan*/  tqmx86_wdt_ops ; 
 int /*<<< orphan*/  tqmx86_wdt_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct tqmx86_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tqmx86_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct tqmx86_wdt *priv;
	struct resource *res;
	int err;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res)
		return -ENODEV;

	priv->io_base = devm_ioport_map(dev, res->start, resource_size(res));
	if (!priv->io_base)
		return -ENOMEM;

	watchdog_set_drvdata(&priv->wdd, priv);

	priv->wdd.parent = dev;
	priv->wdd.info = &tqmx86_wdt_info;
	priv->wdd.ops = &tqmx86_wdt_ops;
	priv->wdd.min_timeout = 1;
	priv->wdd.max_timeout = 4096;
	priv->wdd.max_hw_heartbeat_ms = 4096*1000;
	priv->wdd.timeout = WDT_TIMEOUT;

	watchdog_init_timeout(&priv->wdd, timeout, dev);
	watchdog_set_nowayout(&priv->wdd, WATCHDOG_NOWAYOUT);

	tqmx86_wdt_set_timeout(&priv->wdd, priv->wdd.timeout);

	err = devm_watchdog_register_device(dev, &priv->wdd);
	if (err)
		return err;

	dev_info(dev, "TQMx86 watchdog\n");

	return 0;
}