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
typedef  int u16 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_sw_lkup_type { ____Placeholder_ice_sw_lkup_type } ice_sw_lkup_type ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int ICE_ERR_OUT_OF_RANGE ; 
 int ICE_MAX_VSI ; 
 int ice_aq_alloc_free_vsi_list (struct ice_hw*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_aqc_opc_add_sw_rules ; 
 int /*<<< orphan*/  ice_aqc_opc_alloc_res ; 
 int ice_update_vsi_list_rule (struct ice_hw*,int*,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum ice_status
ice_create_vsi_list_rule(struct ice_hw *hw, u16 *vsi_array, u16 num_vsi,
			 u16 *vsi_list_id, enum ice_sw_lkup_type lkup_type)
{
	enum ice_status status;
	int i;

	for (i = 0; i < num_vsi; i++)
		if (vsi_array[i] >= ICE_MAX_VSI)
			return ICE_ERR_OUT_OF_RANGE;

	status = ice_aq_alloc_free_vsi_list(hw, vsi_list_id, lkup_type,
					    ice_aqc_opc_alloc_res);
	if (status)
		return status;

	/* Update the newly created VSI list to include the specified VSIs */
	return ice_update_vsi_list_rule(hw, vsi_array, num_vsi, *vsi_list_id,
					false, ice_aqc_opc_add_sw_rules,
					lkup_type);
}