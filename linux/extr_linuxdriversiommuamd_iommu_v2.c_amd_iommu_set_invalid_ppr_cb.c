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
struct device_state {int /*<<< orphan*/  inv_ppr_cb; } ;
typedef  int /*<<< orphan*/  amd_iommu_invalid_ppr_cb ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct device_state* __get_device_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  device_id (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  state_lock ; 

int amd_iommu_set_invalid_ppr_cb(struct pci_dev *pdev,
				 amd_iommu_invalid_ppr_cb cb)
{
	struct device_state *dev_state;
	unsigned long flags;
	u16 devid;
	int ret;

	if (!amd_iommu_v2_supported())
		return -ENODEV;

	devid = device_id(pdev);

	spin_lock_irqsave(&state_lock, flags);

	ret = -EINVAL;
	dev_state = __get_device_state(devid);
	if (dev_state == NULL)
		goto out_unlock;

	dev_state->inv_ppr_cb = cb;

	ret = 0;

out_unlock:
	spin_unlock_irqrestore(&state_lock, flags);

	return ret;
}