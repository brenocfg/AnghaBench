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
struct sas_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_add_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_configure_device (int /*<<< orphan*/ *) ; 

int sas_port_add(struct sas_port *port)
{
	int error;

	/* No phys should be added until this is made visible */
	BUG_ON(!list_empty(&port->phy_list));

	error = device_add(&port->dev);

	if (error)
		return error;

	transport_add_device(&port->dev);
	transport_configure_device(&port->dev);

	return 0;
}