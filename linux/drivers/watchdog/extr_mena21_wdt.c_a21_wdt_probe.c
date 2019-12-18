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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bootstatus; struct device* parent; } ;
struct a21_wdt_drv {TYPE_1__ wdt; int /*<<< orphan*/ * gpios; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_ASIS ; 
 int GPIOD_IN ; 
 int GPIO_WD_RST0 ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_GPIOS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDIOF_EXTERN1 ; 
 int /*<<< orphan*/  WDIOF_EXTERN2 ; 
 int /*<<< orphan*/  WDIOF_POWERUNDER ; 
 TYPE_1__ a21_wdt ; 
 unsigned int a21_wdt_get_bootstatus (struct a21_wdt_drv*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct a21_wdt_drv*) ; 
 int /*<<< orphan*/  devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,int) ; 
 struct a21_wdt_drv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,TYPE_1__*) ; 
 int gpiod_count (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_consumer_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int,struct device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct a21_wdt_drv*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a21_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct a21_wdt_drv *drv;
	unsigned int reset = 0;
	int num_gpios;
	int ret;
	int i;

	drv = devm_kzalloc(dev, sizeof(struct a21_wdt_drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	num_gpios = gpiod_count(dev, NULL);
	if (num_gpios != NUM_GPIOS) {
		dev_err(dev, "gpios DT property wrong, got %d want %d",
			num_gpios, NUM_GPIOS);
		return -ENODEV;
	}

	/* Request the used GPIOs */
	for (i = 0; i < num_gpios; i++) {
		enum gpiod_flags gflags;

		if (i < GPIO_WD_RST0)
			gflags = GPIOD_ASIS;
		else
			gflags = GPIOD_IN;
		drv->gpios[i] = devm_gpiod_get_index(dev, NULL, i, gflags);
		if (IS_ERR(drv->gpios[i]))
			return PTR_ERR(drv->gpios[i]);

		gpiod_set_consumer_name(drv->gpios[i], "MEN A21 Watchdog");

		/*
		 * Retrieve the initial value from the GPIOs that should be
		 * output, then set up the line as output with that value.
		 */
		if (i < GPIO_WD_RST0) {
			int val;

			val = gpiod_get_value(drv->gpios[i]);
			gpiod_direction_output(drv->gpios[i], val);
		}
	}

	watchdog_init_timeout(&a21_wdt, 30, dev);
	watchdog_set_nowayout(&a21_wdt, nowayout);
	watchdog_set_drvdata(&a21_wdt, drv);
	a21_wdt.parent = dev;

	reset = a21_wdt_get_bootstatus(drv);
	if (reset == 2)
		a21_wdt.bootstatus |= WDIOF_EXTERN1;
	else if (reset == 4)
		a21_wdt.bootstatus |= WDIOF_CARDRESET;
	else if (reset == 5)
		a21_wdt.bootstatus |= WDIOF_POWERUNDER;
	else if (reset == 7)
		a21_wdt.bootstatus |= WDIOF_EXTERN2;

	drv->wdt = a21_wdt;
	dev_set_drvdata(dev, drv);

	ret = devm_watchdog_register_device(dev, &a21_wdt);
	if (ret)
		return ret;

	dev_info(dev, "MEN A21 watchdog timer driver enabled\n");

	return 0;
}