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
struct mipi_dsi_driver {int (* probe ) (struct mipi_dsi_device*) ;} ;
struct mipi_dsi_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct mipi_dsi_device*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (struct device*) ; 
 struct mipi_dsi_driver* to_mipi_dsi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipi_dsi_drv_probe(struct device *dev)
{
	struct mipi_dsi_driver *drv = to_mipi_dsi_driver(dev->driver);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);

	return drv->probe(dsi);
}