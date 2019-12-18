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
struct mipi_dsi_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device_by_of_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int /*<<< orphan*/  mipi_dsi_bus_type ; 
 struct mipi_dsi_device* to_mipi_dsi_device (struct device*) ; 

struct mipi_dsi_device *of_find_mipi_dsi_device_by_node(struct device_node *np)
{
	struct device *dev;

	dev = bus_find_device_by_of_node(&mipi_dsi_bus_type, np);

	return dev ? to_mipi_dsi_device(dev) : NULL;
}