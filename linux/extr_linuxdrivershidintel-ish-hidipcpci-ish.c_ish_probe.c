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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_flags; } ;
struct ishtp_device {int /*<<< orphan*/  resume_wait; int /*<<< orphan*/  suspend_wait; int /*<<< orphan*/  devc; struct pci_dev* pdev; int /*<<< orphan*/  print_log; } ;
struct ish_hw {int /*<<< orphan*/  mem_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PCI_DEV_FLAGS_NO_D3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct ishtp_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ishtp_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ishtp_device* ish_dev_init (struct pci_dev*) ; 
 int /*<<< orphan*/  ish_event_tracer ; 
 int ish_init (struct ishtp_device*) ; 
 int /*<<< orphan*/  ish_invalid_pci_ids ; 
 int /*<<< orphan*/  ish_irq_handler ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 scalar_t__ pci_dev_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ishtp_device*) ; 
 struct ish_hw* to_ish_hw (struct ishtp_device*) ; 

__attribute__((used)) static int ish_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct ishtp_device *dev;
	struct ish_hw *hw;
	int	ret;

	/* Check for invalid platforms for ISH support */
	if (pci_dev_present(ish_invalid_pci_ids))
		return -ENODEV;

	/* enable pci dev */
	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "ISH: Failed to enable PCI device\n");
		return ret;
	}

	/* set PCI host mastering */
	pci_set_master(pdev);

	/* pci request regions for ISH driver */
	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	if (ret) {
		dev_err(&pdev->dev, "ISH: Failed to get PCI regions\n");
		goto disable_device;
	}

	/* allocates and initializes the ISH dev structure */
	dev = ish_dev_init(pdev);
	if (!dev) {
		ret = -ENOMEM;
		goto release_regions;
	}
	hw = to_ish_hw(dev);
	dev->print_log = ish_event_tracer;

	/* mapping IO device memory */
	hw->mem_addr = pci_iomap(pdev, 0, 0);
	if (!hw->mem_addr) {
		dev_err(&pdev->dev, "ISH: mapping I/O range failure\n");
		ret = -ENOMEM;
		goto free_device;
	}

	dev->pdev = pdev;

	pdev->dev_flags |= PCI_DEV_FLAGS_NO_D3;

	/* request and enable interrupt */
	ret = request_irq(pdev->irq, ish_irq_handler, IRQF_SHARED,
			  KBUILD_MODNAME, dev);
	if (ret) {
		dev_err(&pdev->dev, "ISH: request IRQ failure (%d)\n",
			pdev->irq);
		goto free_device;
	}

	dev_set_drvdata(dev->devc, dev);

	init_waitqueue_head(&dev->suspend_wait);
	init_waitqueue_head(&dev->resume_wait);

	ret = ish_init(dev);
	if (ret)
		goto free_irq;

	return 0;

free_irq:
	free_irq(pdev->irq, dev);
free_device:
	pci_iounmap(pdev, hw->mem_addr);
release_regions:
	pci_release_regions(pdev);
disable_device:
	pci_clear_master(pdev);
	pci_disable_device(pdev);
	dev_err(&pdev->dev, "ISH: PCI driver initialization failed.\n");

	return ret;
}