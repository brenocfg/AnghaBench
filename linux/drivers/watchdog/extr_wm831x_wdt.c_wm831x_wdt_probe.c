#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int /*<<< orphan*/  timeout; struct device* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct wm831x_wdt_drvdata {struct watchdog_device wdt; scalar_t__ update_gpio; struct wm831x* wm831x; int /*<<< orphan*/  lock; } ;
struct wm831x_watchdog_pdata {int primary; int secondary; int software; scalar_t__ update_gpio; } ;
struct wm831x_pdata {struct wm831x_watchdog_pdata* watchdog; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int val; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  WM831X_WATCHDOG ; 
 int WM831X_WDOG_DEBUG ; 
 int WM831X_WDOG_PRIMACT_MASK ; 
 int WM831X_WDOG_PRIMACT_SHIFT ; 
 int WM831X_WDOG_RST_SRC ; 
 int WM831X_WDOG_RST_SRC_SHIFT ; 
 int WM831X_WDOG_SECACT_MASK ; 
 int WM831X_WDOG_SECACT_SHIFT ; 
 int WM831X_WDOG_TO_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm831x_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int devm_gpio_request_one (struct device*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 struct wm831x_wdt_drvdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (struct device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct wm831x_wdt_drvdata*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* wm831x_wdt_cfgs ; 
 int /*<<< orphan*/  wm831x_wdt_info ; 
 int /*<<< orphan*/  wm831x_wdt_ops ; 

__attribute__((used)) static int wm831x_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct wm831x *wm831x = dev_get_drvdata(dev->parent);
	struct wm831x_pdata *chip_pdata = dev_get_platdata(dev->parent);
	struct wm831x_watchdog_pdata *pdata;
	struct wm831x_wdt_drvdata *driver_data;
	struct watchdog_device *wm831x_wdt;
	int reg, ret, i;

	ret = wm831x_reg_read(wm831x, WM831X_WATCHDOG);
	if (ret < 0) {
		dev_err(wm831x->dev, "Failed to read watchdog status: %d\n",
			ret);
		return ret;
	}
	reg = ret;

	if (reg & WM831X_WDOG_DEBUG)
		dev_warn(wm831x->dev, "Watchdog is paused\n");

	driver_data = devm_kzalloc(dev, sizeof(*driver_data), GFP_KERNEL);
	if (!driver_data)
		return -ENOMEM;

	mutex_init(&driver_data->lock);
	driver_data->wm831x = wm831x;

	wm831x_wdt = &driver_data->wdt;

	wm831x_wdt->info = &wm831x_wdt_info;
	wm831x_wdt->ops = &wm831x_wdt_ops;
	wm831x_wdt->parent = dev;
	watchdog_set_nowayout(wm831x_wdt, nowayout);
	watchdog_set_drvdata(wm831x_wdt, driver_data);

	reg = wm831x_reg_read(wm831x, WM831X_WATCHDOG);
	reg &= WM831X_WDOG_TO_MASK;
	for (i = 0; i < ARRAY_SIZE(wm831x_wdt_cfgs); i++)
		if (wm831x_wdt_cfgs[i].val == reg)
			break;
	if (i == ARRAY_SIZE(wm831x_wdt_cfgs))
		dev_warn(wm831x->dev,
			 "Unknown watchdog timeout: %x\n", reg);
	else
		wm831x_wdt->timeout = wm831x_wdt_cfgs[i].time;

	/* Apply any configuration */
	if (chip_pdata)
		pdata = chip_pdata->watchdog;
	else
		pdata = NULL;

	if (pdata) {
		reg &= ~(WM831X_WDOG_SECACT_MASK | WM831X_WDOG_PRIMACT_MASK |
			 WM831X_WDOG_RST_SRC);

		reg |= pdata->primary << WM831X_WDOG_PRIMACT_SHIFT;
		reg |= pdata->secondary << WM831X_WDOG_SECACT_SHIFT;
		reg |= pdata->software << WM831X_WDOG_RST_SRC_SHIFT;

		if (pdata->update_gpio) {
			ret = devm_gpio_request_one(dev, pdata->update_gpio,
						    GPIOF_OUT_INIT_LOW,
						    "Watchdog update");
			if (ret < 0) {
				dev_err(wm831x->dev,
					"Failed to request update GPIO: %d\n",
					ret);
				return ret;
			}

			driver_data->update_gpio = pdata->update_gpio;

			/* Make sure the watchdog takes hardware updates */
			reg |= WM831X_WDOG_RST_SRC;
		}

		ret = wm831x_reg_unlock(wm831x);
		if (ret == 0) {
			ret = wm831x_reg_write(wm831x, WM831X_WATCHDOG, reg);
			wm831x_reg_lock(wm831x);
		} else {
			dev_err(wm831x->dev,
				"Failed to unlock security key: %d\n", ret);
			return ret;
		}
	}

	return devm_watchdog_register_device(dev, &driver_data->wdt);
}