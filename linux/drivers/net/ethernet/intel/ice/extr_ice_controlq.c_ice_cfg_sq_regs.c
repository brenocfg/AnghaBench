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
struct ice_hw {int dummy; } ;
struct ice_ctl_q_info {int /*<<< orphan*/  num_sq_entries; int /*<<< orphan*/  sq; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_cfg_cq_regs (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ice_status
ice_cfg_sq_regs(struct ice_hw *hw, struct ice_ctl_q_info *cq)
{
	return ice_cfg_cq_regs(hw, &cq->sq, cq->num_sq_entries);
}