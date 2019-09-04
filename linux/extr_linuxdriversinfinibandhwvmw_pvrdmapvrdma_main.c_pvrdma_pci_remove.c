#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {int /*<<< orphan*/ * notifier_call; } ;
struct pvrdma_dev {int /*<<< orphan*/  ib_dev; TYPE_1__ driver_uar; int /*<<< orphan*/  qp_tbl; int /*<<< orphan*/  srq_tbl; int /*<<< orphan*/  cq_tbl; int /*<<< orphan*/  sgid_tbl; int /*<<< orphan*/  regs; int /*<<< orphan*/  async_pdir; int /*<<< orphan*/  cq_pdir; int /*<<< orphan*/  device_link; int /*<<< orphan*/ * netdev; TYPE_2__ nb_netdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVRDMA_DEVICE_CTL_RESET ; 
 int /*<<< orphan*/  PVRDMA_REG_CTL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct pvrdma_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvrdma_device_list_lock ; 
 int /*<<< orphan*/  pvrdma_disable_intrs (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_free_irq (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_free_slots (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvrdma_uar_table_cleanup (struct pvrdma_dev*) ; 
 int /*<<< orphan*/  pvrdma_write_reg (struct pvrdma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (TYPE_2__*) ; 

__attribute__((used)) static void pvrdma_pci_remove(struct pci_dev *pdev)
{
	struct pvrdma_dev *dev = pci_get_drvdata(pdev);

	if (!dev)
		return;

	dev_info(&pdev->dev, "detaching from device\n");

	unregister_netdevice_notifier(&dev->nb_netdev);
	dev->nb_netdev.notifier_call = NULL;

	flush_workqueue(event_wq);

	if (dev->netdev) {
		dev_put(dev->netdev);
		dev->netdev = NULL;
	}

	/* Unregister ib device */
	ib_unregister_device(&dev->ib_dev);

	mutex_lock(&pvrdma_device_list_lock);
	list_del(&dev->device_link);
	mutex_unlock(&pvrdma_device_list_lock);

	pvrdma_disable_intrs(dev);
	pvrdma_free_irq(dev);
	pci_free_irq_vectors(pdev);

	/* Deactivate pvrdma device */
	pvrdma_write_reg(dev, PVRDMA_REG_CTL, PVRDMA_DEVICE_CTL_RESET);
	pvrdma_page_dir_cleanup(dev, &dev->cq_pdir);
	pvrdma_page_dir_cleanup(dev, &dev->async_pdir);
	pvrdma_free_slots(dev);

	iounmap(dev->regs);
	kfree(dev->sgid_tbl);
	kfree(dev->cq_tbl);
	kfree(dev->srq_tbl);
	kfree(dev->qp_tbl);
	pvrdma_uar_table_cleanup(dev);
	iounmap(dev->driver_uar.map);

	ib_dealloc_device(&dev->ib_dev);

	/* Free pci resources */
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}