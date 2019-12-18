#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  reset_work; } ;
struct nvme_dev {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CTRL_DEAD ; 
 int /*<<< orphan*/  NVME_CTRL_DELETING ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_change_ctrl_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_dev_disable (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  nvme_dev_remove_admin (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_dev_unmap (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_free_host_mem (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_free_queues (struct nvme_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_put_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_release_cmb (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_release_prp_pools (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_remove_namespaces (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_stop_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_uninit_ctrl (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_device_is_present (struct pci_dev*) ; 
 struct nvme_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_remove(struct pci_dev *pdev)
{
	struct nvme_dev *dev = pci_get_drvdata(pdev);

	nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DELETING);
	pci_set_drvdata(pdev, NULL);

	if (!pci_device_is_present(pdev)) {
		nvme_change_ctrl_state(&dev->ctrl, NVME_CTRL_DEAD);
		nvme_dev_disable(dev, true);
		nvme_dev_remove_admin(dev);
	}

	flush_work(&dev->ctrl.reset_work);
	nvme_stop_ctrl(&dev->ctrl);
	nvme_remove_namespaces(&dev->ctrl);
	nvme_dev_disable(dev, true);
	nvme_release_cmb(dev);
	nvme_free_host_mem(dev);
	nvme_dev_remove_admin(dev);
	nvme_free_queues(dev, 0);
	nvme_uninit_ctrl(&dev->ctrl);
	nvme_release_prp_pools(dev);
	nvme_dev_unmap(dev);
	nvme_put_ctrl(&dev->ctrl);
}