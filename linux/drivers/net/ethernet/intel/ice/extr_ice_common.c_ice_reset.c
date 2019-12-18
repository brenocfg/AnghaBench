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
typedef  int /*<<< orphan*/  u32 ;
struct ice_hw {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
typedef  enum ice_reset_req { ____Placeholder_ice_reset_req } ice_reset_req ;

/* Variables and functions */
 int /*<<< orphan*/  GLGEN_RTRIG ; 
 int /*<<< orphan*/  GLGEN_RTRIG_CORER_M ; 
 int /*<<< orphan*/  GLGEN_RTRIG_GLOBR_M ; 
 int /*<<< orphan*/  ICE_DBG_INIT ; 
 int ICE_ERR_PARAM ; 
#define  ICE_RESET_CORER 130 
#define  ICE_RESET_GLOBR 129 
#define  ICE_RESET_PFR 128 
 int ice_check_reset (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ice_flush (struct ice_hw*) ; 
 int ice_pf_reset (struct ice_hw*) ; 
 int /*<<< orphan*/  rd32 (struct ice_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct ice_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum ice_status ice_reset(struct ice_hw *hw, enum ice_reset_req req)
{
	u32 val = 0;

	switch (req) {
	case ICE_RESET_PFR:
		return ice_pf_reset(hw);
	case ICE_RESET_CORER:
		ice_debug(hw, ICE_DBG_INIT, "CoreR requested\n");
		val = GLGEN_RTRIG_CORER_M;
		break;
	case ICE_RESET_GLOBR:
		ice_debug(hw, ICE_DBG_INIT, "GlobalR requested\n");
		val = GLGEN_RTRIG_GLOBR_M;
		break;
	default:
		return ICE_ERR_PARAM;
	}

	val |= rd32(hw, GLGEN_RTRIG);
	wr32(hw, GLGEN_RTRIG, val);
	ice_flush(hw);

	/* wait for the FW to be ready */
	return ice_check_reset(hw);
}