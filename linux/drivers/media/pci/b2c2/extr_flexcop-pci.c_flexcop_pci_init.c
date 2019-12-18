#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct flexcop_pci {TYPE_1__* pdev; int /*<<< orphan*/  io_mem; int /*<<< orphan*/  init_state; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EIO ; 
 int /*<<< orphan*/  FC_PCI_INIT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  flexcop_pci_isr ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_iomap (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 int pci_request_regions (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,struct flexcop_pci*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flexcop_pci*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flexcop_pci_init(struct flexcop_pci *fc_pci)
{
	int ret;

	info("card revision %x", fc_pci->pdev->revision);

	if ((ret = pci_enable_device(fc_pci->pdev)) != 0)
		return ret;
	pci_set_master(fc_pci->pdev);

	if ((ret = pci_request_regions(fc_pci->pdev, DRIVER_NAME)) != 0)
		goto err_pci_disable_device;

	fc_pci->io_mem = pci_iomap(fc_pci->pdev, 0, 0x800);

	if (!fc_pci->io_mem) {
		err("cannot map io memory\n");
		ret = -EIO;
		goto err_pci_release_regions;
	}

	pci_set_drvdata(fc_pci->pdev, fc_pci);
	spin_lock_init(&fc_pci->irq_lock);
	if ((ret = request_irq(fc_pci->pdev->irq, flexcop_pci_isr,
					IRQF_SHARED, DRIVER_NAME, fc_pci)) != 0)
		goto err_pci_iounmap;

	fc_pci->init_state |= FC_PCI_INIT;
	return ret;

err_pci_iounmap:
	pci_iounmap(fc_pci->pdev, fc_pci->io_mem);
err_pci_release_regions:
	pci_release_regions(fc_pci->pdev);
err_pci_disable_device:
	pci_disable_device(fc_pci->pdev);
	return ret;
}