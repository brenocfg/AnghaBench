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
struct pcie_pme_service_data {struct pcie_device* srv; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct pcie_device {int /*<<< orphan*/  irq; struct pci_dev* port; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  kfree (struct pcie_pme_service_data*) ; 
 struct pcie_pme_service_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_clear_root_pme_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_pme_interrupt_enable (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcie_pme_irq ; 
 int /*<<< orphan*/  pcie_pme_mark_devices (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_pme_work_fn ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcie_device*) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,struct pcie_pme_service_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcie_pme_probe(struct pcie_device *srv)
{
	struct pci_dev *port;
	struct pcie_pme_service_data *data;
	int ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	spin_lock_init(&data->lock);
	INIT_WORK(&data->work, pcie_pme_work_fn);
	data->srv = srv;
	set_service_data(srv, data);

	port = srv->port;
	pcie_pme_interrupt_enable(port, false);
	pcie_clear_root_pme_status(port);

	ret = request_irq(srv->irq, pcie_pme_irq, IRQF_SHARED, "PCIe PME", srv);
	if (ret) {
		kfree(data);
		return ret;
	}

	pci_info(port, "Signaling with IRQ %d\n", srv->irq);

	pcie_pme_mark_devices(port);
	pcie_pme_interrupt_enable(port, true);
	return 0;
}