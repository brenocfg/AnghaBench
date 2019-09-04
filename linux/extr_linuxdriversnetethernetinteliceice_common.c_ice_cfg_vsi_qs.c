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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ice_port_info {scalar_t__ port_state; int /*<<< orphan*/  sched_lock; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_CFG ; 
 size_t ICE_MAX_TRAFFIC_CLASS ; 
 scalar_t__ ICE_SCHED_PORT_STATE_READY ; 
 int /*<<< orphan*/  ice_is_tc_ena (size_t,size_t) ; 
 int ice_sched_cfg_vsi (struct ice_port_info*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_sched_get_tc_node (struct ice_port_info*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status
ice_cfg_vsi_qs(struct ice_port_info *pi, u16 vsi_id, u8 tc_bitmap,
	       u16 *maxqs, u8 owner)
{
	enum ice_status status = 0;
	u8 i;

	if (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		return ICE_ERR_CFG;

	mutex_lock(&pi->sched_lock);

	for (i = 0; i < ICE_MAX_TRAFFIC_CLASS; i++) {
		/* configuration is possible only if TC node is present */
		if (!ice_sched_get_tc_node(pi, i))
			continue;

		status = ice_sched_cfg_vsi(pi, vsi_id, i, maxqs[i], owner,
					   ice_is_tc_ena(tc_bitmap, i));
		if (status)
			break;
	}

	mutex_unlock(&pi->sched_lock);
	return status;
}