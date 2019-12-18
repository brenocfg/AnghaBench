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
typedef  int u16 ;
struct wm831x {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_RTC_WRITE_COUNTER ; 
 int /*<<< orphan*/  add_device_randomness (int*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm831x_rtc_add_randomness(struct wm831x *wm831x)
{
	int ret;
	u16 reg;

	/*
	 * The write counter contains a pseudo-random number which is
	 * regenerated every time we set the RTC so it should be a
	 * useful per-system source of entropy.
	 */
	ret = wm831x_reg_read(wm831x, WM831X_RTC_WRITE_COUNTER);
	if (ret >= 0) {
		reg = ret;
		add_device_randomness(&reg, sizeof(reg));
	} else {
		dev_warn(wm831x->dev, "Failed to read RTC write counter: %d\n",
			 ret);
	}
}