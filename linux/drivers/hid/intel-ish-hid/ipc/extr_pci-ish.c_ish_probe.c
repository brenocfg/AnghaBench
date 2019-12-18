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
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  msix_enabled; int /*<<< orphan*/  msi_enabled; struct device dev; } ;
struct ishtp_device {int /*<<< orphan*/  resume_wait; int /*<<< orphan*/  suspend_wait; int /*<<< orphan*/  devc; struct pci_dev* pdev; int /*<<< orphan*/  print_log; } ;
struct ish_hw {int /*<<< orphan*/  mem_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 unsigned long IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PCI_IRQ_ALL_TYPES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct ishtp_device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct ishtp_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ishtp_device* ish_dev_init (struct pci_dev*) ; 
 int /*<<< orphan*/  ish_event_tracer ; 
 int ish_init (struct ishtp_device*) ; 
 int /*<<< orphan*/  ish_invalid_pci_ids ; 
 int /*<<< orphan*/  ish_irq_handler ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dev_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 struct ish_hw* to_ish_hw (struct ishtp_device*) ; 

__attribute__((used)) static int ish_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int ret;
	struct ish_hw *hw;
	unsigned long irq_flag = 0;
	struct ishtp_device *ishtp;
	struct device *dev = &pdev->dev;

	/* Check for invalid platforms for ISH support */
	if (pci_dev_present(ish_invalid_pci_ids))
		return -ENODEV;

	/* enable pci dev */
	ret = pcim_enable_device(pdev);
	if (ret) {
		dev_err(dev, "ISH: Failed to enable PCI device\n");
		return ret;
	}

	/* set PCI host mastering */
	pci_set_master(pdev);

	/* pci request regions for ISH driver */
	ret = pcim_iomap_regions(pdev, 1 << 0, KBUILD_MODNAME);
	if (ret) {
		dev_err(dev, "ISH: Failed to get PCI regions\n");
		return ret;
	}

	/* allocates and initializes the ISH dev structure */
	ishtp = ish_dev_init(pdev);
	if (!ishtp) {
		ret = -ENOMEM;
		return ret;
	}
	hw = to_ish_hw(ishtp);
	ishtp->print_log = ish_event_tracer;

	/* mapping IO device memory */
	hw->mem_addr = pcim_iomap_table(pdev)[0];
	ishtp->pdev = pdev;

	/* request and enable interrupt */
	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	if (!pdev->msi_enabled && !pdev->msix_enabled)
		irq_flag = IRQF_SHARED;

	ret = devm_request_irq(dev, pdev->irq, ish_irq_handler,
			       irq_flag, KBUILD_MODNAME, ishtp);
	if (ret) {
		dev_err(dev, "ISH: request IRQ %d failed\n", pdev->irq);
		return ret;
	}

	dev_set_drvdata(ishtp->devc, ishtp);

	init_waitqueue_head(&ishtp->suspend_wait);
	init_waitqueue_head(&ishtp->resume_wait);

	ret = ish_init(ishtp);
	if (ret)
		return ret;

	return 0;
}