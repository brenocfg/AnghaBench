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
struct spi_device {int dummy; } ;

/* Variables and functions */
 struct wm831x* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  wm831x_device_exit (struct wm831x*) ; 

__attribute__((used)) static int wm831x_spi_remove(struct spi_device *spi)
{
	struct wm831x *wm831x = spi_get_drvdata(spi);

	wm831x_device_exit(wm831x);

	return 0;
}