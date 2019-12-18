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
struct wm831x {int /*<<< orphan*/  dev; scalar_t__ soft_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_CHIP_ON ; 
 int /*<<< orphan*/  WM831X_POWER_STATE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wm831x_device_shutdown(struct wm831x *wm831x)
{
	if (wm831x->soft_shutdown) {
		dev_info(wm831x->dev, "Initiating shutdown...\n");
		wm831x_set_bits(wm831x, WM831X_POWER_STATE, WM831X_CHIP_ON, 0);
	}
}