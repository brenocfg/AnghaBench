#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_svm {TYPE_1__* mm; } ;
struct intel_iommu {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct intel_svm* intel_pasid_lookup_id (int) ; 
 struct intel_iommu* intel_svm_device_to_iommu (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pasid_mutex ; 

int intel_svm_is_pasid_valid(struct device *dev, int pasid)
{
	struct intel_iommu *iommu;
	struct intel_svm *svm;
	int ret = -EINVAL;

	mutex_lock(&pasid_mutex);
	iommu = intel_svm_device_to_iommu(dev);
	if (!iommu)
		goto out;

	svm = intel_pasid_lookup_id(pasid);
	if (!svm)
		goto out;

	/* init_mm is used in this case */
	if (!svm->mm)
		ret = 1;
	else if (atomic_read(&svm->mm->mm_users) > 0)
		ret = 1;
	else
		ret = 0;

 out:
	mutex_unlock(&pasid_mutex);

	return ret;
}