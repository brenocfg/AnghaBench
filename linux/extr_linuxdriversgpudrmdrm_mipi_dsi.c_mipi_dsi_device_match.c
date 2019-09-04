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
struct mipi_dsi_device {int /*<<< orphan*/  name; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (struct device*) ; 

__attribute__((used)) static int mipi_dsi_device_match(struct device *dev, struct device_driver *drv)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	/* attempt OF style match */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* compare DSI device and driver names */
	if (!strcmp(dsi->name, drv->name))
		return 1;

	return 0;
}