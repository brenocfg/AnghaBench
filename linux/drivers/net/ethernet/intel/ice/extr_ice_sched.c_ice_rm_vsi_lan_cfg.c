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
struct ice_port_info {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_SCHED_NODE_OWNER_LAN ; 
 int ice_sched_rm_vsi_cfg (struct ice_port_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum ice_status ice_rm_vsi_lan_cfg(struct ice_port_info *pi, u16 vsi_handle)
{
	return ice_sched_rm_vsi_cfg(pi, vsi_handle, ICE_SCHED_NODE_OWNER_LAN);
}