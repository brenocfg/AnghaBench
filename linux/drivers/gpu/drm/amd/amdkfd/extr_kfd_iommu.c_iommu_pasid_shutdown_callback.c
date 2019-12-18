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
struct pci_dev {int dummy; } ;
struct kfd_process_device {int dummy; } ;
struct kfd_process {scalar_t__ pasid; int /*<<< orphan*/  mutex; } ;
struct kfd_dev {TYPE_1__* dbgmgr; } ;
struct TYPE_3__ {scalar_t__ pasid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfd_dbgmgr_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  kfd_dbgmgr_unregister (TYPE_1__*,struct kfd_process*) ; 
 struct kfd_dev* kfd_device_by_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/ * kfd_get_dbgmgr_mutex () ; 
 struct kfd_process_device* kfd_get_process_device_data (struct kfd_dev*,struct kfd_process*) ; 
 struct kfd_process* kfd_lookup_process_by_pasid (int) ; 
 int /*<<< orphan*/  kfd_process_dequeue_from_device (struct kfd_process_device*) ; 
 int /*<<< orphan*/  kfd_unref_process (struct kfd_process*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static void iommu_pasid_shutdown_callback(struct pci_dev *pdev, int pasid)
{
	struct kfd_dev *dev = kfd_device_by_pci_dev(pdev);
	struct kfd_process *p;
	struct kfd_process_device *pdd;

	if (!dev)
		return;

	/*
	 * Look for the process that matches the pasid. If there is no such
	 * process, we either released it in amdkfd's own notifier, or there
	 * is a bug. Unfortunately, there is no way to tell...
	 */
	p = kfd_lookup_process_by_pasid(pasid);
	if (!p)
		return;

	pr_debug("Unbinding process %d from IOMMU\n", pasid);

	mutex_lock(kfd_get_dbgmgr_mutex());

	if (dev->dbgmgr && dev->dbgmgr->pasid == p->pasid) {
		if (!kfd_dbgmgr_unregister(dev->dbgmgr, p)) {
			kfd_dbgmgr_destroy(dev->dbgmgr);
			dev->dbgmgr = NULL;
		}
	}

	mutex_unlock(kfd_get_dbgmgr_mutex());

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	if (pdd)
		/* For GPU relying on IOMMU, we need to dequeue here
		 * when PASID is still bound.
		 */
		kfd_process_dequeue_from_device(pdd);

	mutex_unlock(&p->mutex);

	kfd_unref_process(p);
}