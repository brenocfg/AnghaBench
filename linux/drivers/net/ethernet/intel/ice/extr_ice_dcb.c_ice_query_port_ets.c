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
struct ice_port_info {int /*<<< orphan*/  sched_lock; } ;
struct ice_aqc_port_ets_elem {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ice_aq_query_port_ets (struct ice_port_info*,struct ice_aqc_port_ets_elem*,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 
 int ice_update_port_tc_tree_cfg (struct ice_port_info*,struct ice_aqc_port_ets_elem*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

enum ice_status
ice_query_port_ets(struct ice_port_info *pi,
		   struct ice_aqc_port_ets_elem *buf, u16 buf_size,
		   struct ice_sq_cd *cd)
{
	enum ice_status status;

	mutex_lock(&pi->sched_lock);
	status = ice_aq_query_port_ets(pi, buf, buf_size, cd);
	if (!status)
		status = ice_update_port_tc_tree_cfg(pi, buf);
	mutex_unlock(&pi->sched_lock);
	return status;
}