#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wm831x_wdt_drvdata {int /*<<< orphan*/  lock; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_WATCHDOG ; 
 int /*<<< orphan*/  WM831X_WDOG_ENA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm831x_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_wdt_start(struct watchdog_device *wdt_dev)
{
	struct wm831x_wdt_drvdata *driver_data = watchdog_get_drvdata(wdt_dev);
	struct wm831x *wm831x = driver_data->wm831x;
	int ret;

	mutex_lock(&driver_data->lock);

	ret = wm831x_reg_unlock(wm831x);
	if (ret == 0) {
		ret = wm831x_set_bits(wm831x, WM831X_WATCHDOG,
				      WM831X_WDOG_ENA, WM831X_WDOG_ENA);
		wm831x_reg_lock(wm831x);
	} else {
		dev_err(wm831x->dev, "Failed to unlock security key: %d\n",
			ret);
	}

	mutex_unlock(&driver_data->lock);

	return ret;
}