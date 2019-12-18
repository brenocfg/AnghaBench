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
struct ice_vsi_ctx {int /*<<< orphan*/  vsi_num; } ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_PARAM ; 
 int ice_aq_update_vsi (struct ice_hw*,struct ice_vsi_ctx*,struct ice_sq_cd*) ; 
 int /*<<< orphan*/  ice_get_hw_vsi_num (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_is_vsi_valid (struct ice_hw*,int /*<<< orphan*/ ) ; 

enum ice_status
ice_update_vsi(struct ice_hw *hw, u16 vsi_handle, struct ice_vsi_ctx *vsi_ctx,
	       struct ice_sq_cd *cd)
{
	if (!ice_is_vsi_valid(hw, vsi_handle))
		return ICE_ERR_PARAM;
	vsi_ctx->vsi_num = ice_get_hw_vsi_num(hw, vsi_handle);
	return ice_aq_update_vsi(hw, vsi_ctx, cd);
}