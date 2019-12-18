#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct ilo_hwinfo {TYPE_1__ cdev; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  alloc_lock; struct pci_dev* ilo_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILO_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int MAX_CCB ; 
 int MAX_ILO_DEV ; 
 int MIN_CCB ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_device (struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_blacklist ; 
 int /*<<< orphan*/  ilo_class ; 
 int /*<<< orphan*/  ilo_disable_interrupts (struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_enable_interrupts (struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_fops ; 
 int* ilo_hwdev ; 
 int /*<<< orphan*/  ilo_isr ; 
 int /*<<< orphan*/  ilo_major ; 
 int ilo_map_device (struct pci_dev*,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_unmap_device (struct pci_dev*,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  kfree (struct ilo_hwinfo*) ; 
 struct ilo_hwinfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max_ccb ; 
 int pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ilo_probe(struct pci_dev *pdev,
			       const struct pci_device_id *ent)
{
	int devnum, minor, start, error = 0;
	struct ilo_hwinfo *ilo_hw;

	if (pci_match_id(ilo_blacklist, pdev)) {
		dev_dbg(&pdev->dev, "Not supported on this device\n");
		return -ENODEV;
	}

	if (max_ccb > MAX_CCB)
		max_ccb = MAX_CCB;
	else if (max_ccb < MIN_CCB)
		max_ccb = MIN_CCB;

	/* find a free range for device files */
	for (devnum = 0; devnum < MAX_ILO_DEV; devnum++) {
		if (ilo_hwdev[devnum] == 0) {
			ilo_hwdev[devnum] = 1;
			break;
		}
	}

	if (devnum == MAX_ILO_DEV) {
		dev_err(&pdev->dev, "Error finding free device\n");
		return -ENODEV;
	}

	/* track global allocations for this device */
	error = -ENOMEM;
	ilo_hw = kzalloc(sizeof(*ilo_hw), GFP_KERNEL);
	if (!ilo_hw)
		goto out;

	ilo_hw->ilo_dev = pdev;
	spin_lock_init(&ilo_hw->alloc_lock);
	spin_lock_init(&ilo_hw->fifo_lock);
	spin_lock_init(&ilo_hw->open_lock);

	error = pci_enable_device(pdev);
	if (error)
		goto free;

	pci_set_master(pdev);

	error = pci_request_regions(pdev, ILO_NAME);
	if (error)
		goto disable;

	error = ilo_map_device(pdev, ilo_hw);
	if (error)
		goto free_regions;

	pci_set_drvdata(pdev, ilo_hw);
	clear_device(ilo_hw);

	error = request_irq(pdev->irq, ilo_isr, IRQF_SHARED, "hpilo", ilo_hw);
	if (error)
		goto unmap;

	ilo_enable_interrupts(ilo_hw);

	cdev_init(&ilo_hw->cdev, &ilo_fops);
	ilo_hw->cdev.owner = THIS_MODULE;
	start = devnum * max_ccb;
	error = cdev_add(&ilo_hw->cdev, MKDEV(ilo_major, start), max_ccb);
	if (error) {
		dev_err(&pdev->dev, "Could not add cdev\n");
		goto remove_isr;
	}

	for (minor = 0 ; minor < max_ccb; minor++) {
		struct device *dev;
		dev = device_create(ilo_class, &pdev->dev,
				    MKDEV(ilo_major, minor), NULL,
				    "hpilo!d%dccb%d", devnum, minor);
		if (IS_ERR(dev))
			dev_err(&pdev->dev, "Could not create files\n");
	}

	return 0;
remove_isr:
	ilo_disable_interrupts(ilo_hw);
	free_irq(pdev->irq, ilo_hw);
unmap:
	ilo_unmap_device(pdev, ilo_hw);
free_regions:
	pci_release_regions(pdev);
disable:
/*	pci_disable_device(pdev);  see comment in ilo_remove */
free:
	kfree(ilo_hw);
out:
	ilo_hwdev[devnum] = 0;
	return error;
}