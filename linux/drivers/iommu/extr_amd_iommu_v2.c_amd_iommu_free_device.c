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
struct device_state {int /*<<< orphan*/  count; int /*<<< orphan*/  wq; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct device_state* __get_device_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_id (struct pci_dev*) ; 
 int /*<<< orphan*/  free_device_state (struct device_state*) ; 
 int /*<<< orphan*/  free_pasid_states (struct device_state*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device_state (struct device_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  state_lock ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void amd_iommu_free_device(struct pci_dev *pdev)
{
	struct device_state *dev_state;
	unsigned long flags;
	u16 devid;

	if (!amd_iommu_v2_supported())
		return;

	devid = device_id(pdev);

	spin_lock_irqsave(&state_lock, flags);

	dev_state = __get_device_state(devid);
	if (dev_state == NULL) {
		spin_unlock_irqrestore(&state_lock, flags);
		return;
	}

	list_del(&dev_state->list);

	spin_unlock_irqrestore(&state_lock, flags);

	/* Get rid of any remaining pasid states */
	free_pasid_states(dev_state);

	put_device_state(dev_state);
	/*
	 * Wait until the last reference is dropped before freeing
	 * the device state.
	 */
	wait_event(dev_state->wq, !atomic_read(&dev_state->count));
	free_device_state(dev_state);
}