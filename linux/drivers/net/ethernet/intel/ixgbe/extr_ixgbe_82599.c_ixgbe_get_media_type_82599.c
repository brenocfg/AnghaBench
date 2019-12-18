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
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {int device_id; TYPE_1__ phy; } ;
typedef  enum ixgbe_media_type { ____Placeholder_ixgbe_media_type } ixgbe_media_type ;

/* Variables and functions */
#define  IXGBE_DEV_ID_82599EN_SFP 145 
#define  IXGBE_DEV_ID_82599_BACKPLANE_FCOE 144 
#define  IXGBE_DEV_ID_82599_COMBO_BACKPLANE 143 
#define  IXGBE_DEV_ID_82599_CX4 142 
#define  IXGBE_DEV_ID_82599_KR 141 
#define  IXGBE_DEV_ID_82599_KX4 140 
#define  IXGBE_DEV_ID_82599_KX4_MEZZ 139 
#define  IXGBE_DEV_ID_82599_LS 138 
#define  IXGBE_DEV_ID_82599_QSFP_SF_QP 137 
#define  IXGBE_DEV_ID_82599_SFP 136 
#define  IXGBE_DEV_ID_82599_SFP_EM 135 
#define  IXGBE_DEV_ID_82599_SFP_FCOE 134 
#define  IXGBE_DEV_ID_82599_SFP_SF2 133 
#define  IXGBE_DEV_ID_82599_SFP_SF_QP 132 
#define  IXGBE_DEV_ID_82599_T3_LOM 131 
#define  IXGBE_DEV_ID_82599_XAUI_LOM 130 
 int ixgbe_media_type_backplane ; 
 int ixgbe_media_type_copper ; 
 int ixgbe_media_type_cx4 ; 
 int ixgbe_media_type_fiber ; 
 int ixgbe_media_type_fiber_lco ; 
 int ixgbe_media_type_fiber_qsfp ; 
 int ixgbe_media_type_unknown ; 
#define  ixgbe_phy_cu_unknown 129 
#define  ixgbe_phy_tn 128 

__attribute__((used)) static enum ixgbe_media_type ixgbe_get_media_type_82599(struct ixgbe_hw *hw)
{
	/* Detect if there is a copper PHY attached. */
	switch (hw->phy.type) {
	case ixgbe_phy_cu_unknown:
	case ixgbe_phy_tn:
		return ixgbe_media_type_copper;

	default:
		break;
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
	case IXGBE_DEV_ID_82599_KR:
	case IXGBE_DEV_ID_82599_BACKPLANE_FCOE:
	case IXGBE_DEV_ID_82599_XAUI_LOM:
		/* Default device ID is mezzanine card KX/KX4 */
		return ixgbe_media_type_backplane;

	case IXGBE_DEV_ID_82599_SFP:
	case IXGBE_DEV_ID_82599_SFP_FCOE:
	case IXGBE_DEV_ID_82599_SFP_EM:
	case IXGBE_DEV_ID_82599_SFP_SF2:
	case IXGBE_DEV_ID_82599_SFP_SF_QP:
	case IXGBE_DEV_ID_82599EN_SFP:
		return ixgbe_media_type_fiber;

	case IXGBE_DEV_ID_82599_CX4:
		return ixgbe_media_type_cx4;

	case IXGBE_DEV_ID_82599_T3_LOM:
		return ixgbe_media_type_copper;

	case IXGBE_DEV_ID_82599_LS:
		return ixgbe_media_type_fiber_lco;

	case IXGBE_DEV_ID_82599_QSFP_SF_QP:
		return ixgbe_media_type_fiber_qsfp;

	default:
		return ixgbe_media_type_unknown;
	}
}