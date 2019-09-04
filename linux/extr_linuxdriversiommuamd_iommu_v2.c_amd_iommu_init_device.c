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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct iommu_group {int dummy; } ;
struct device_state {int max_pasids; int /*<<< orphan*/ * states; int /*<<< orphan*/ * domain; int /*<<< orphan*/  list; int /*<<< orphan*/  count; scalar_t__ pasid_levels; int /*<<< orphan*/  devid; struct pci_dev* pdev; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PASID_MASK ; 
 int /*<<< orphan*/ * __get_device_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_domain_direct_map (int /*<<< orphan*/ *) ; 
 int amd_iommu_domain_enable_v2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_id (struct pci_dev*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int iommu_attach_group (int /*<<< orphan*/ *,struct iommu_group*) ; 
 int /*<<< orphan*/ * iommu_domain_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_domain_free (int /*<<< orphan*/ *) ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  kfree (struct device_state*) ; 
 struct device_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  state_list ; 
 int /*<<< orphan*/  state_lock ; 

int amd_iommu_init_device(struct pci_dev *pdev, int pasids)
{
	struct device_state *dev_state;
	struct iommu_group *group;
	unsigned long flags;
	int ret, tmp;
	u16 devid;

	might_sleep();

	if (!amd_iommu_v2_supported())
		return -ENODEV;

	if (pasids <= 0 || pasids > (PASID_MASK + 1))
		return -EINVAL;

	devid = device_id(pdev);

	dev_state = kzalloc(sizeof(*dev_state), GFP_KERNEL);
	if (dev_state == NULL)
		return -ENOMEM;

	spin_lock_init(&dev_state->lock);
	init_waitqueue_head(&dev_state->wq);
	dev_state->pdev  = pdev;
	dev_state->devid = devid;

	tmp = pasids;
	for (dev_state->pasid_levels = 0; (tmp - 1) & ~0x1ff; tmp >>= 9)
		dev_state->pasid_levels += 1;

	atomic_set(&dev_state->count, 1);
	dev_state->max_pasids = pasids;

	ret = -ENOMEM;
	dev_state->states = (void *)get_zeroed_page(GFP_KERNEL);
	if (dev_state->states == NULL)
		goto out_free_dev_state;

	dev_state->domain = iommu_domain_alloc(&pci_bus_type);
	if (dev_state->domain == NULL)
		goto out_free_states;

	amd_iommu_domain_direct_map(dev_state->domain);

	ret = amd_iommu_domain_enable_v2(dev_state->domain, pasids);
	if (ret)
		goto out_free_domain;

	group = iommu_group_get(&pdev->dev);
	if (!group) {
		ret = -EINVAL;
		goto out_free_domain;
	}

	ret = iommu_attach_group(dev_state->domain, group);
	if (ret != 0)
		goto out_drop_group;

	iommu_group_put(group);

	spin_lock_irqsave(&state_lock, flags);

	if (__get_device_state(devid) != NULL) {
		spin_unlock_irqrestore(&state_lock, flags);
		ret = -EBUSY;
		goto out_free_domain;
	}

	list_add_tail(&dev_state->list, &state_list);

	spin_unlock_irqrestore(&state_lock, flags);

	return 0;

out_drop_group:
	iommu_group_put(group);

out_free_domain:
	iommu_domain_free(dev_state->domain);

out_free_states:
	free_page((unsigned long)dev_state->states);

out_free_dev_state:
	kfree(dev_state);

	return ret;
}