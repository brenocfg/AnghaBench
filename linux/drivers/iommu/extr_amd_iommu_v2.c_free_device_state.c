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
struct iommu_group {int dummy; } ;
struct device_state {int /*<<< orphan*/  domain; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_detach_group (int /*<<< orphan*/ ,struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_domain_free (int /*<<< orphan*/ ) ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  kfree (struct device_state*) ; 

__attribute__((used)) static void free_device_state(struct device_state *dev_state)
{
	struct iommu_group *group;

	/*
	 * First detach device from domain - No more PRI requests will arrive
	 * from that device after it is unbound from the IOMMUv2 domain.
	 */
	group = iommu_group_get(&dev_state->pdev->dev);
	if (WARN_ON(!group))
		return;

	iommu_detach_group(dev_state->domain, group);

	iommu_group_put(group);

	/* Everything is down now, free the IOMMUv2 domain */
	iommu_domain_free(dev_state->domain);

	/* Finally get rid of the device-state */
	kfree(dev_state);
}