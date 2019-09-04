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
struct fault {int /*<<< orphan*/  tag; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  address; int /*<<< orphan*/  pasid; TYPE_1__* dev_state; } ;
struct TYPE_2__ {int (* inv_ppr_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
#define  AMD_IOMMU_INV_PRI_RSP_FAIL 130 
#define  AMD_IOMMU_INV_PRI_RSP_INVALID 129 
#define  AMD_IOMMU_INV_PRI_RSP_SUCCESS 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  PPR_FAILURE ; 
 int /*<<< orphan*/  PPR_INVALID ; 
 int /*<<< orphan*/  PPR_SUCCESS ; 
 int /*<<< orphan*/  set_pri_tag_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_fault_error(struct fault *fault)
{
	int status;

	if (!fault->dev_state->inv_ppr_cb) {
		set_pri_tag_status(fault->state, fault->tag, PPR_INVALID);
		return;
	}

	status = fault->dev_state->inv_ppr_cb(fault->dev_state->pdev,
					      fault->pasid,
					      fault->address,
					      fault->flags);
	switch (status) {
	case AMD_IOMMU_INV_PRI_RSP_SUCCESS:
		set_pri_tag_status(fault->state, fault->tag, PPR_SUCCESS);
		break;
	case AMD_IOMMU_INV_PRI_RSP_INVALID:
		set_pri_tag_status(fault->state, fault->tag, PPR_INVALID);
		break;
	case AMD_IOMMU_INV_PRI_RSP_FAIL:
		set_pri_tag_status(fault->state, fault->tag, PPR_FAILURE);
		break;
	default:
		BUG();
	}
}