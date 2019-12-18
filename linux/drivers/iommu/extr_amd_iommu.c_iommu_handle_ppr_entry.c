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
typedef  int /*<<< orphan*/  u64 ;
struct amd_iommu_fault {int /*<<< orphan*/  flags; int /*<<< orphan*/  tag; int /*<<< orphan*/  device_id; int /*<<< orphan*/  pasid; int /*<<< orphan*/  address; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPR_DEVID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPR_FLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPR_PASID (int /*<<< orphan*/ ) ; 
 scalar_t__ PPR_REQ_FAULT ; 
 scalar_t__ PPR_REQ_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPR_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct amd_iommu_fault*) ; 
 int /*<<< orphan*/  ppr_notifier ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 

__attribute__((used)) static void iommu_handle_ppr_entry(struct amd_iommu *iommu, u64 *raw)
{
	struct amd_iommu_fault fault;

	if (PPR_REQ_TYPE(raw[0]) != PPR_REQ_FAULT) {
		pr_err_ratelimited("Unknown PPR request received\n");
		return;
	}

	fault.address   = raw[1];
	fault.pasid     = PPR_PASID(raw[0]);
	fault.device_id = PPR_DEVID(raw[0]);
	fault.tag       = PPR_TAG(raw[0]);
	fault.flags     = PPR_FLAGS(raw[0]);

	atomic_notifier_call_chain(&ppr_notifier, 0, &fault);
}