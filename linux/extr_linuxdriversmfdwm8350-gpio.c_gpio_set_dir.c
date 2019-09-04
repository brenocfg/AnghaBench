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
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_GPIO_CONFIGURATION_I_O ; 
 int WM8350_GPIO_DIR_OUT ; 
 int wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_reg_lock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_reg_unlock (struct wm8350*) ; 
 int wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_set_dir(struct wm8350 *wm8350, int gpio, int dir)
{
	int ret;

	wm8350_reg_unlock(wm8350);
	if (dir == WM8350_GPIO_DIR_OUT)
		ret = wm8350_clear_bits(wm8350,
					WM8350_GPIO_CONFIGURATION_I_O,
					1 << gpio);
	else
		ret = wm8350_set_bits(wm8350,
				      WM8350_GPIO_CONFIGURATION_I_O,
				      1 << gpio);
	wm8350_reg_lock(wm8350);
	return ret;
}