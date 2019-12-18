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
typedef  int u16 ;
struct ice_hw {int dummy; } ;
struct ice_aqc_get_elem {TYPE_1__* generic; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  node_teid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_SCHED ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ice_aq_query_sched_elems (struct ice_hw*,int,struct ice_aqc_get_elem*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct ice_aqc_get_elem*,int /*<<< orphan*/ ,int) ; 

enum ice_status
ice_sched_query_elem(struct ice_hw *hw, u32 node_teid,
		     struct ice_aqc_get_elem *buf)
{
	u16 buf_size, num_elem_ret = 0;
	enum ice_status status;

	buf_size = sizeof(*buf);
	memset(buf, 0, buf_size);
	buf->generic[0].node_teid = cpu_to_le32(node_teid);
	status = ice_aq_query_sched_elems(hw, 1, buf, buf_size, &num_elem_ret,
					  NULL);
	if (status || num_elem_ret != 1)
		ice_debug(hw, ICE_DBG_SCHED, "query element failed\n");
	return status;
}