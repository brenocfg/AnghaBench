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
struct wm831x {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct wm831x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  wm831x_device_shutdown (struct wm831x*) ; 

__attribute__((used)) static int wm831x_spi_poweroff(struct device *dev)
{
	struct wm831x *wm831x = dev_get_drvdata(dev);

	wm831x_device_shutdown(wm831x);

	return 0;
}