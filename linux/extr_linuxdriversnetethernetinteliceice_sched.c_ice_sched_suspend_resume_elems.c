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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ice_hw {int dummy; } ;
struct ice_aqc_suspend_resume_elem {int /*<<< orphan*/ * teid; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int ICE_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct ice_aqc_suspend_resume_elem*) ; 
 struct ice_aqc_suspend_resume_elem* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ice_aq_resume_sched_elems (struct ice_hw*,int,struct ice_aqc_suspend_resume_elem*,int,int*,int /*<<< orphan*/ *) ; 
 int ice_aq_suspend_sched_elems (struct ice_hw*,int,struct ice_aqc_suspend_resume_elem*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 

__attribute__((used)) static enum ice_status
ice_sched_suspend_resume_elems(struct ice_hw *hw, u8 num_nodes, u32 *node_teids,
			       bool suspend)
{
	struct ice_aqc_suspend_resume_elem *buf;
	u16 i, buf_size, num_elem_ret = 0;
	enum ice_status status;

	buf_size = sizeof(*buf) * num_nodes;
	buf = devm_kzalloc(ice_hw_to_dev(hw), buf_size, GFP_KERNEL);
	if (!buf)
		return ICE_ERR_NO_MEMORY;

	for (i = 0; i < num_nodes; i++)
		buf->teid[i] = cpu_to_le32(node_teids[i]);

	if (suspend)
		status = ice_aq_suspend_sched_elems(hw, num_nodes, buf,
						    buf_size, &num_elem_ret,
						    NULL);
	else
		status = ice_aq_resume_sched_elems(hw, num_nodes, buf,
						   buf_size, &num_elem_ret,
						   NULL);
	if (status || num_elem_ret != num_nodes)
		ice_debug(hw, ICE_DBG_SCHED, "suspend/resume failed\n");

	devm_kfree(ice_hw_to_dev(hw), buf);
	return status;
}