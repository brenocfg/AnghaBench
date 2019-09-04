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
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct phantom_device {int /*<<< orphan*/ * caddr; int /*<<< orphan*/ * iaddr; int /*<<< orphan*/ * oaddr; TYPE_1__ cdev; int /*<<< orphan*/  wait; int /*<<< orphan*/  regs_lock; int /*<<< orphan*/  open_lock; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PHANTOM_MAX_MINORS ; 
 int PHN_IRQCTL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct phantom_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct phantom_device*) ; 
 struct phantom_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct phantom_device*) ; 
 int /*<<< orphan*/  phantom_class ; 
 int* phantom_devices ; 
 int /*<<< orphan*/  phantom_file_ops ; 
 unsigned int phantom_get_free () ; 
 int /*<<< orphan*/  phantom_isr ; 
 int /*<<< orphan*/  phantom_major ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct phantom_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phantom_probe(struct pci_dev *pdev,
	const struct pci_device_id *pci_id)
{
	struct phantom_device *pht;
	unsigned int minor;
	int retval;

	retval = pci_enable_device(pdev);
	if (retval) {
		dev_err(&pdev->dev, "pci_enable_device failed!\n");
		goto err;
	}

	minor = phantom_get_free();
	if (minor == PHANTOM_MAX_MINORS) {
		dev_err(&pdev->dev, "too many devices found!\n");
		retval = -EIO;
		goto err_dis;
	}

	phantom_devices[minor] = 1;

	retval = pci_request_regions(pdev, "phantom");
	if (retval) {
		dev_err(&pdev->dev, "pci_request_regions failed!\n");
		goto err_null;
	}

	retval = -ENOMEM;
	pht = kzalloc(sizeof(*pht), GFP_KERNEL);
	if (pht == NULL) {
		dev_err(&pdev->dev, "unable to allocate device\n");
		goto err_reg;
	}

	pht->caddr = pci_iomap(pdev, 0, 0);
	if (pht->caddr == NULL) {
		dev_err(&pdev->dev, "can't remap conf space\n");
		goto err_fr;
	}
	pht->iaddr = pci_iomap(pdev, 2, 0);
	if (pht->iaddr == NULL) {
		dev_err(&pdev->dev, "can't remap input space\n");
		goto err_unmc;
	}
	pht->oaddr = pci_iomap(pdev, 3, 0);
	if (pht->oaddr == NULL) {
		dev_err(&pdev->dev, "can't remap output space\n");
		goto err_unmi;
	}

	mutex_init(&pht->open_lock);
	spin_lock_init(&pht->regs_lock);
	init_waitqueue_head(&pht->wait);
	cdev_init(&pht->cdev, &phantom_file_ops);
	pht->cdev.owner = THIS_MODULE;

	iowrite32(0, pht->caddr + PHN_IRQCTL);
	ioread32(pht->caddr + PHN_IRQCTL); /* PCI posting */
	retval = request_irq(pdev->irq, phantom_isr,
			IRQF_SHARED, "phantom", pht);
	if (retval) {
		dev_err(&pdev->dev, "can't establish ISR\n");
		goto err_unmo;
	}

	retval = cdev_add(&pht->cdev, MKDEV(phantom_major, minor), 1);
	if (retval) {
		dev_err(&pdev->dev, "chardev registration failed\n");
		goto err_irq;
	}

	if (IS_ERR(device_create(phantom_class, &pdev->dev,
				 MKDEV(phantom_major, minor), NULL,
				 "phantom%u", minor)))
		dev_err(&pdev->dev, "can't create device\n");

	pci_set_drvdata(pdev, pht);

	return 0;
err_irq:
	free_irq(pdev->irq, pht);
err_unmo:
	pci_iounmap(pdev, pht->oaddr);
err_unmi:
	pci_iounmap(pdev, pht->iaddr);
err_unmc:
	pci_iounmap(pdev, pht->caddr);
err_fr:
	kfree(pht);
err_reg:
	pci_release_regions(pdev);
err_null:
	phantom_devices[minor] = 0;
err_dis:
	pci_disable_device(pdev);
err:
	return retval;
}