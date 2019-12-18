#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; char* handler_name; struct hv_pcibus_device* data; int /*<<< orphan*/  handler; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct hv_pcibus_device {TYPE_2__* hdev; int /*<<< orphan*/  irq_domain; TYPE_3__ msi_info; TYPE_1__ sysdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENODEV ; 
 int MSI_FLAG_MULTI_PCI_MSI ; 
 int MSI_FLAG_PCI_MSIX ; 
 int MSI_FLAG_USE_DEF_CHIP_OPS ; 
 int MSI_FLAG_USE_DEF_DOM_OPS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  hv_msi_irq_chip ; 
 int /*<<< orphan*/  hv_msi_ops ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_vector_domain ; 

__attribute__((used)) static int hv_pcie_init_irq_domain(struct hv_pcibus_device *hbus)
{
	hbus->msi_info.chip = &hv_msi_irq_chip;
	hbus->msi_info.ops = &hv_msi_ops;
	hbus->msi_info.flags = (MSI_FLAG_USE_DEF_DOM_OPS |
		MSI_FLAG_USE_DEF_CHIP_OPS | MSI_FLAG_MULTI_PCI_MSI |
		MSI_FLAG_PCI_MSIX);
	hbus->msi_info.handler = handle_edge_irq;
	hbus->msi_info.handler_name = "edge";
	hbus->msi_info.data = hbus;
	hbus->irq_domain = pci_msi_create_irq_domain(hbus->sysdata.fwnode,
						     &hbus->msi_info,
						     x86_vector_domain);
	if (!hbus->irq_domain) {
		dev_err(&hbus->hdev->device,
			"Failed to build an MSI IRQ domain\n");
		return -ENODEV;
	}

	return 0;
}