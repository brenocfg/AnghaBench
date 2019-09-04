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
struct wm8994 {int cust_id; int revision; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  WM8994_GPIO_6 128 
 struct wm8994* dev_get_drvdata (struct device*) ; 
 int wm8994_volatile_register (struct device*,unsigned int) ; 

__attribute__((used)) static bool wm1811_volatile_register(struct device *dev, unsigned int reg)
{
	struct wm8994 *wm8994 = dev_get_drvdata(dev);

	switch (reg) {
	case WM8994_GPIO_6:
		if (wm8994->cust_id > 1 || wm8994->revision > 1)
			return true;
		else
			return false;
	default:
		return wm8994_volatile_register(dev, reg);
	}
}