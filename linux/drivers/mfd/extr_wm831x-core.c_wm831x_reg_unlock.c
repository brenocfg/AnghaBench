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
struct wm831x {int /*<<< orphan*/  io_lock; scalar_t__ locked; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WM831X_SECURITY_KEY ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,int) ; 

int wm831x_reg_unlock(struct wm831x *wm831x)
{
	int ret;

	/* 0x9716 is the value required to unlock the registers */
	ret = wm831x_reg_write(wm831x, WM831X_SECURITY_KEY, 0x9716);
	if (ret == 0) {
		dev_vdbg(wm831x->dev, "Registers unlocked\n");

		mutex_lock(&wm831x->io_lock);
		WARN_ON(!wm831x->locked);
		wm831x->locked = 0;
		mutex_unlock(&wm831x->io_lock);
	}

	return ret;
}