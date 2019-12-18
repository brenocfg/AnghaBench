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
struct wm831x {int locked; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WM831X_SECURITY_KEY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wm831x_reg_lock(struct wm831x *wm831x)
{
	int ret;

	ret = wm831x_reg_write(wm831x, WM831X_SECURITY_KEY, 0);
	if (ret == 0) {
		dev_vdbg(wm831x->dev, "Registers locked\n");

		mutex_lock(&wm831x->io_lock);
		WARN_ON(wm831x->locked);
		wm831x->locked = 1;
		mutex_unlock(&wm831x->io_lock);
	} else {
		dev_err(wm831x->dev, "Failed to lock registers: %d\n", ret);
	}

}