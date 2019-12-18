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
typedef  scalar_t__ u16 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 scalar_t__ ICE_MAIN_VSI_HANDLE ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,scalar_t__) ; 
 int ice_replay_pre_init (struct ice_hw*) ; 
 int ice_replay_vsi_all_fltr (struct ice_hw*,scalar_t__) ; 

enum ice_status ice_replay_vsi(struct ice_hw *hw, u16 vsi_handle)
{
	enum ice_status status;

	if (!ice_is_vsi_valid(hw, vsi_handle))
		return ICE_ERR_PARAM;

	/* Replay pre-initialization if there is any */
	if (vsi_handle == ICE_MAIN_VSI_HANDLE) {
		status = ice_replay_pre_init(hw);
		if (status)
			return status;
	}

	/* Replay per VSI all filters */
	status = ice_replay_vsi_all_fltr(hw, vsi_handle);
	return status;
}