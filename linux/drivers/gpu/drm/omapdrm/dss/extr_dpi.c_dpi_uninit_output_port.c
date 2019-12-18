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
struct omap_dss_device {int dummy; } ;
struct dpi_data {struct omap_dss_device output; } ;
struct device_node {struct dpi_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapdss_device_cleanup_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_device_unregister (struct omap_dss_device*) ; 

__attribute__((used)) static void dpi_uninit_output_port(struct device_node *port)
{
	struct dpi_data *dpi = port->data;
	struct omap_dss_device *out = &dpi->output;

	omapdss_device_unregister(out);
	omapdss_device_cleanup_output(out);
}