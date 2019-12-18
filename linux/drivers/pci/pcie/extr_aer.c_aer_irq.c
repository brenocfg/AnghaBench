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
struct pcie_device {int dummy; } ;
struct pci_dev {int aer_cap; } ;
struct aer_rpc {int /*<<< orphan*/  aer_fifo; struct pci_dev* rpd; } ;
struct aer_err_source {int status; int id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int PCI_ERR_ROOT_COR_RCV ; 
 scalar_t__ PCI_ERR_ROOT_ERR_SRC ; 
 scalar_t__ PCI_ERR_ROOT_STATUS ; 
 int PCI_ERR_ROOT_UNCOR_RCV ; 
 struct aer_rpc* get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,struct aer_err_source) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static irqreturn_t aer_irq(int irq, void *context)
{
	struct pcie_device *pdev = (struct pcie_device *)context;
	struct aer_rpc *rpc = get_service_data(pdev);
	struct pci_dev *rp = rpc->rpd;
	struct aer_err_source e_src = {};
	int pos = rp->aer_cap;

	pci_read_config_dword(rp, pos + PCI_ERR_ROOT_STATUS, &e_src.status);
	if (!(e_src.status & (PCI_ERR_ROOT_UNCOR_RCV|PCI_ERR_ROOT_COR_RCV)))
		return IRQ_NONE;

	pci_read_config_dword(rp, pos + PCI_ERR_ROOT_ERR_SRC, &e_src.id);
	pci_write_config_dword(rp, pos + PCI_ERR_ROOT_STATUS, e_src.status);

	if (!kfifo_put(&rpc->aer_fifo, e_src))
		return IRQ_HANDLED;

	return IRQ_WAKE_THREAD;
}