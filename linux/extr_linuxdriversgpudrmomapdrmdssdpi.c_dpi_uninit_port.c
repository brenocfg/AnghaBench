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
struct dpi_data {int dummy; } ;
struct device_node {struct dpi_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpi_uninit_output_port (struct device_node*) ; 

void dpi_uninit_port(struct device_node *port)
{
	struct dpi_data *dpi = port->data;

	if (!dpi)
		return;

	dpi_uninit_output_port(port);
}