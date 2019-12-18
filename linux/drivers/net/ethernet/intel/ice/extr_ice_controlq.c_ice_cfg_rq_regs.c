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
typedef  int /*<<< orphan*/  u32 ;
struct ice_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct ice_ctl_q_info {int num_rq_entries; TYPE_1__ rq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_cfg_cq_regs (struct ice_hw*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_cfg_rq_regs(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	enum ice_status status;

	status = ice_cfg_cq_regs(hw, &cq->rq, cq->num_rq_entries);
	if (status)
		return status;

	/* Update tail in the HW to post pre-allocated buffers */
	wr32(hw, cq->rq.tail, (u32)(cq->num_rq_entries - 1));

	return 0;
}