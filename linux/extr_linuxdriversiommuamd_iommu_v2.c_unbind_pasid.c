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
struct pasid_state {int invalid; int /*<<< orphan*/  pasid; TYPE_1__* device_state; } ;
struct iommu_domain {int dummy; } ;
struct TYPE_2__ {struct iommu_domain* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_domain_clear_gcr3 (struct iommu_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_wq ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void unbind_pasid(struct pasid_state *pasid_state)
{
	struct iommu_domain *domain;

	domain = pasid_state->device_state->domain;

	/*
	 * Mark pasid_state as invalid, no more faults will we added to the
	 * work queue after this is visible everywhere.
	 */
	pasid_state->invalid = true;

	/* Make sure this is visible */
	smp_wmb();

	/* After this the device/pasid can't access the mm anymore */
	amd_iommu_domain_clear_gcr3(domain, pasid_state->pasid);

	/* Make sure no more pending faults are in the queue */
	flush_workqueue(iommu_wq);
}