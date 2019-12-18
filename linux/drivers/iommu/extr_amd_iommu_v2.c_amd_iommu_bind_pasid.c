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
typedef  int /*<<< orphan*/  u16 ;
struct task_struct {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct pasid_state {int pasid; int invalid; TYPE_1__ mn; struct mm_struct* mm; struct device_state* device_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; int /*<<< orphan*/  count; } ;
struct mm_struct {int /*<<< orphan*/  pgd; } ;
struct device_state {int max_pasids; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int amd_iommu_domain_set_gcr3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd_iommu_v2_supported () ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_pasid_state (struct device_state*,int) ; 
 int /*<<< orphan*/  device_id (struct pci_dev*) ; 
 int /*<<< orphan*/  free_pasid_state (struct pasid_state*) ; 
 struct device_state* get_device_state (int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_mn ; 
 struct pasid_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_register (TYPE_1__*,struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (TYPE_1__*,struct mm_struct*) ; 
 int /*<<< orphan*/  put_device_state (struct device_state*) ; 
 int set_pasid_state (struct device_state*,struct pasid_state*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int amd_iommu_bind_pasid(struct pci_dev *pdev, int pasid,
			 struct task_struct *task)
{
	struct pasid_state *pasid_state;
	struct device_state *dev_state;
	struct mm_struct *mm;
	u16 devid;
	int ret;

	might_sleep();

	if (!amd_iommu_v2_supported())
		return -ENODEV;

	devid     = device_id(pdev);
	dev_state = get_device_state(devid);

	if (dev_state == NULL)
		return -EINVAL;

	ret = -EINVAL;
	if (pasid < 0 || pasid >= dev_state->max_pasids)
		goto out;

	ret = -ENOMEM;
	pasid_state = kzalloc(sizeof(*pasid_state), GFP_KERNEL);
	if (pasid_state == NULL)
		goto out;


	atomic_set(&pasid_state->count, 1);
	init_waitqueue_head(&pasid_state->wq);
	spin_lock_init(&pasid_state->lock);

	mm                        = get_task_mm(task);
	pasid_state->mm           = mm;
	pasid_state->device_state = dev_state;
	pasid_state->pasid        = pasid;
	pasid_state->invalid      = true; /* Mark as valid only if we are
					     done with setting up the pasid */
	pasid_state->mn.ops       = &iommu_mn;

	if (pasid_state->mm == NULL)
		goto out_free;

	mmu_notifier_register(&pasid_state->mn, mm);

	ret = set_pasid_state(dev_state, pasid_state, pasid);
	if (ret)
		goto out_unregister;

	ret = amd_iommu_domain_set_gcr3(dev_state->domain, pasid,
					__pa(pasid_state->mm->pgd));
	if (ret)
		goto out_clear_state;

	/* Now we are ready to handle faults */
	pasid_state->invalid = false;

	/*
	 * Drop the reference to the mm_struct here. We rely on the
	 * mmu_notifier release call-back to inform us when the mm
	 * is going away.
	 */
	mmput(mm);

	return 0;

out_clear_state:
	clear_pasid_state(dev_state, pasid);

out_unregister:
	mmu_notifier_unregister(&pasid_state->mn, mm);
	mmput(mm);

out_free:
	free_pasid_state(pasid_state);

out:
	put_device_state(dev_state);

	return ret;
}