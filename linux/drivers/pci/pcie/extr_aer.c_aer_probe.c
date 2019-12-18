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
struct device {int dummy; } ;
struct pcie_device {int /*<<< orphan*/  irq; struct pci_dev* port; struct device device; } ;
struct pci_dev {int dummy; } ;
struct aer_rpc {struct pci_dev* rpd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  aer_enable_rootport (struct aer_rpc*) ; 
 int /*<<< orphan*/  aer_irq ; 
 int /*<<< orphan*/  aer_isr ; 
 struct aer_rpc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcie_device*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,struct aer_rpc*) ; 

__attribute__((used)) static int aer_probe(struct pcie_device *dev)
{
	int status;
	struct aer_rpc *rpc;
	struct device *device = &dev->device;
	struct pci_dev *port = dev->port;

	rpc = devm_kzalloc(device, sizeof(struct aer_rpc), GFP_KERNEL);
	if (!rpc)
		return -ENOMEM;

	rpc->rpd = port;
	set_service_data(dev, rpc);

	status = devm_request_threaded_irq(device, dev->irq, aer_irq, aer_isr,
					   IRQF_SHARED, "aerdrv", dev);
	if (status) {
		pci_err(port, "request AER IRQ %d failed\n", dev->irq);
		return status;
	}

	aer_enable_rootport(rpc);
	pci_info(port, "enabled with IRQ %d\n", dev->irq);
	return 0;
}