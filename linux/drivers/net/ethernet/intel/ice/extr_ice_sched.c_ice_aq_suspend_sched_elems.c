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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
struct ice_aqc_suspend_resume_elem {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ice_aqc_opc_suspend_sched_elems ; 
 int ice_aqc_send_sched_elem_cmd (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ice_sq_cd*) ; 

__attribute__((used)) static enum ice_status
ice_aq_suspend_sched_elems(struct ice_hw *hw, u16 elems_req,
			   struct ice_aqc_suspend_resume_elem *buf,
			   u16 buf_size, u16 *elems_ret, struct ice_sq_cd *cd)
{
	return ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_suspend_sched_elems,
					   elems_req, (void *)buf, buf_size,
					   elems_ret, cd);
}