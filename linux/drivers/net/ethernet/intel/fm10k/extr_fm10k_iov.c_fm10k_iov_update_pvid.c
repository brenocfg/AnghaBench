#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct fm10k_vf_info {size_t sw_vid; } ;
struct fm10k_iov_data {size_t num_vfs; struct fm10k_vf_info* vf_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* assign_default_mac_vlan ) (struct fm10k_hw*,struct fm10k_vf_info*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {size_t dglort_map; } ;
struct fm10k_hw {TYPE_3__ iov; TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; struct fm10k_iov_data* iov_data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t FM10K_DGLORTMAP_NONE ; 
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_vf_info*) ; 

s32 fm10k_iov_update_pvid(struct fm10k_intfc *interface, u16 glort, u16 pvid)
{
	struct fm10k_iov_data *iov_data = interface->iov_data;
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_vf_info *vf_info;
	u16 vf_idx = (glort - hw->mac.dglort_map) & FM10K_DGLORTMAP_NONE;

	/* no IOV support, not our message to process */
	if (!iov_data)
		return FM10K_ERR_PARAM;

	/* glort outside our range, not our message to process */
	if (vf_idx >= iov_data->num_vfs)
		return FM10K_ERR_PARAM;

	/* determine if an update has occurred and if so notify the VF */
	vf_info = &iov_data->vf_info[vf_idx];
	if (vf_info->sw_vid != pvid) {
		vf_info->sw_vid = pvid;
		hw->iov.ops.assign_default_mac_vlan(hw, vf_info);
	}

	return 0;
}