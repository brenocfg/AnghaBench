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
struct sas_port {int /*<<< orphan*/  phy_list; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct sas_port* dev_to_sas_port (struct device*) ; 
 int /*<<< orphan*/  kfree (struct sas_port*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_port_release(struct device *dev)
{
	struct sas_port *port = dev_to_sas_port(dev);

	BUG_ON(!list_empty(&port->phy_list));

	put_device(dev->parent);
	kfree(port);
}