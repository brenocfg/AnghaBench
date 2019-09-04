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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ default_vid; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FM10K_ERR_PARAM ; 
 scalar_t__ FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FM10K_PF_ATTR_ID_UPDATE_PVID ; 
 scalar_t__ FM10K_VLAN_TABLE_VID_MAX ; 
 int /*<<< orphan*/  UPDATE_PVID_GLORT ; 
 int /*<<< orphan*/  UPDATE_PVID_PVID ; 
 int /*<<< orphan*/  fm10k_glort_valid_pf (struct fm10k_hw*,scalar_t__) ; 
 scalar_t__ fm10k_tlv_attr_get_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 fm10k_msg_update_pvid_pf(struct fm10k_hw *hw, u32 **results,
				    struct fm10k_mbx_info *mbx)
{
	u16 glort, pvid;
	u32 pvid_update;
	s32 err;

	err = fm10k_tlv_attr_get_u32(results[FM10K_PF_ATTR_ID_UPDATE_PVID],
				     &pvid_update);
	if (err)
		return err;

	/* extract values from the pvid update */
	glort = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_GLORT);
	pvid = FM10K_MSG_HDR_FIELD_GET(pvid_update, UPDATE_PVID_PVID);

	/* if glort is not valid return error */
	if (!fm10k_glort_valid_pf(hw, glort))
		return FM10K_ERR_PARAM;

	/* verify VLAN ID is valid */
	if (pvid >= FM10K_VLAN_TABLE_VID_MAX)
		return FM10K_ERR_PARAM;

	/* record the port VLAN ID value */
	hw->mac.default_vid = pvid;

	return 0;
}