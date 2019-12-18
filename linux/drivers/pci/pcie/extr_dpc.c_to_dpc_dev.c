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
struct pci_dev {int dummy; } ;
struct dpc_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PORT_SERVICE_DPC ; 
 struct dpc_dev* get_service_data (int /*<<< orphan*/ ) ; 
 struct device* pcie_port_find_device (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pcie_device (struct device*) ; 

__attribute__((used)) static struct dpc_dev *to_dpc_dev(struct pci_dev *dev)
{
	struct device *device;

	device = pcie_port_find_device(dev, PCIE_PORT_SERVICE_DPC);
	if (!device)
		return NULL;
	return get_service_data(to_pcie_device(device));
}