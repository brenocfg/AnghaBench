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
typedef  size_t u16 ;
struct pasid_state {int /*<<< orphan*/  lock; TYPE_1__* pri; int /*<<< orphan*/  pasid; } ;
struct device_state {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int finish; int /*<<< orphan*/  status; int /*<<< orphan*/  inflight; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPR_SUCCESS ; 
 int /*<<< orphan*/  amd_iommu_complete_ppr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void finish_pri_tag(struct device_state *dev_state,
			   struct pasid_state *pasid_state,
			   u16 tag)
{
	unsigned long flags;

	spin_lock_irqsave(&pasid_state->lock, flags);
	if (atomic_dec_and_test(&pasid_state->pri[tag].inflight) &&
	    pasid_state->pri[tag].finish) {
		amd_iommu_complete_ppr(dev_state->pdev, pasid_state->pasid,
				       pasid_state->pri[tag].status, tag);
		pasid_state->pri[tag].finish = false;
		pasid_state->pri[tag].status = PPR_SUCCESS;
	}
	spin_unlock_irqrestore(&pasid_state->lock, flags);
}