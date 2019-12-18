#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  io; } ;
struct mt7621_pcie {int /*<<< orphan*/  busn; TYPE_1__ offset; int /*<<< orphan*/  mem; int /*<<< orphan*/  io; struct device* dev; } ;
struct list_head {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int devm_request_pci_bus_resources (struct device*,struct list_head*) ; 
 int /*<<< orphan*/  pci_add_resource (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_add_resource_offset (struct list_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7621_pcie_request_resources(struct mt7621_pcie *pcie,
					 struct list_head *res)
{
	struct device *dev = pcie->dev;

	pci_add_resource_offset(res, &pcie->io, pcie->offset.io);
	pci_add_resource_offset(res, &pcie->mem, pcie->offset.mem);
	pci_add_resource(res, &pcie->busn);

	return devm_request_pci_bus_resources(dev, res);
}