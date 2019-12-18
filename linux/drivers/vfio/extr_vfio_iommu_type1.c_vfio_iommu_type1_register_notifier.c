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
struct vfio_iommu {int /*<<< orphan*/  notifier; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long VFIO_IOMMU_NOTIFY_DMA_UNMAP ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

__attribute__((used)) static int vfio_iommu_type1_register_notifier(void *iommu_data,
					      unsigned long *events,
					      struct notifier_block *nb)
{
	struct vfio_iommu *iommu = iommu_data;

	/* clear known events */
	*events &= ~VFIO_IOMMU_NOTIFY_DMA_UNMAP;

	/* refuse to register if still events remaining */
	if (*events)
		return -EINVAL;

	return blocking_notifier_chain_register(&iommu->notifier, nb);
}