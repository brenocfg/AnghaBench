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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct pasid_state {int /*<<< orphan*/  mm; int /*<<< orphan*/  mn; int /*<<< orphan*/  pasid; } ;
struct device_state {int max_pasids; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  clear_pasid_state (struct device_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_id (struct pci_dev*) ; 
 struct device_state* get_device_state (int /*<<< orphan*/ ) ; 
 struct pasid_state* get_pasid_state (struct device_state*,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device_state (struct device_state*) ; 
 int /*<<< orphan*/  put_pasid_state (struct pasid_state*) ; 
 int /*<<< orphan*/  put_pasid_state_wait (struct pasid_state*) ; 

void amd_iommu_unbind_pasid(struct pci_dev *pdev, int pasid)
{
	struct pasid_state *pasid_state;
	struct device_state *dev_state;
	u16 devid;

	might_sleep();

	if (!amd_iommu_v2_supported())
		return;

	devid = device_id(pdev);
	dev_state = get_device_state(devid);
	if (dev_state == NULL)
		return;

	if (pasid < 0 || pasid >= dev_state->max_pasids)
		goto out;

	pasid_state = get_pasid_state(dev_state, pasid);
	if (pasid_state == NULL)
		goto out;
	/*
	 * Drop reference taken here. We are safe because we still hold
	 * the reference taken in the amd_iommu_bind_pasid function.
	 */
	put_pasid_state(pasid_state);

	/* Clear the pasid state so that the pasid can be re-used */
	clear_pasid_state(dev_state, pasid_state->pasid);

	/*
	 * Call mmu_notifier_unregister to drop our reference
	 * to pasid_state->mm
	 */
	mmu_notifier_unregister(&pasid_state->mn, pasid_state->mm);

	put_pasid_state_wait(pasid_state); /* Reference taken in
					      amd_iommu_bind_pasid */
out:
	/* Drop reference taken in this function */
	put_device_state(dev_state);

	/* Drop reference taken in amd_iommu_bind_pasid */
	put_device_state(dev_state);
}