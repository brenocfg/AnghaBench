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
struct pasid_state {int /*<<< orphan*/  pasid; struct device_state* device_state; } ;
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;
struct device_state {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  amd_iommu_flush_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  amd_iommu_flush_tlb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pasid_state* mn_to_state (struct mmu_notifier*) ; 

__attribute__((used)) static void mn_invalidate_range(struct mmu_notifier *mn,
				struct mm_struct *mm,
				unsigned long start, unsigned long end)
{
	struct pasid_state *pasid_state;
	struct device_state *dev_state;

	pasid_state = mn_to_state(mn);
	dev_state   = pasid_state->device_state;

	if ((start ^ (end - 1)) < PAGE_SIZE)
		amd_iommu_flush_page(dev_state->domain, pasid_state->pasid,
				     start);
	else
		amd_iommu_flush_tlb(dev_state->domain, pasid_state->pasid);
}