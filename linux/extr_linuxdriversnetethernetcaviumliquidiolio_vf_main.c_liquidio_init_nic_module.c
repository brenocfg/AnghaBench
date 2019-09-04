#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {int ifcount; TYPE_1__* pci_dev; TYPE_2__* props; } ;
struct octdev_props {int dummy; } ;
struct TYPE_4__ {int gmxport; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_OCTEON_LINKS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int setup_nic_devices (struct octeon_device*) ; 

__attribute__((used)) static int liquidio_init_nic_module(struct octeon_device *oct)
{
	int num_nic_ports = 1;
	int i, retval = 0;

	dev_dbg(&oct->pci_dev->dev, "Initializing network interfaces\n");

	/* only default iq and oq were initialized
	 * initialize the rest as well run port_config command for each port
	 */
	oct->ifcount = num_nic_ports;
	memset(oct->props, 0,
	       sizeof(struct octdev_props) * num_nic_ports);

	for (i = 0; i < MAX_OCTEON_LINKS; i++)
		oct->props[i].gmxport = -1;

	retval = setup_nic_devices(oct);
	if (retval) {
		dev_err(&oct->pci_dev->dev, "Setup NIC devices failed\n");
		goto octnet_init_failure;
	}

	dev_dbg(&oct->pci_dev->dev, "Network interfaces ready\n");

	return retval;

octnet_init_failure:

	oct->ifcount = 0;

	return retval;
}