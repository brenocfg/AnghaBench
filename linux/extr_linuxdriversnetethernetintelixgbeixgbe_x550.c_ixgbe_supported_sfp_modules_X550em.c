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
struct TYPE_2__ {int sfp_type; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_SFP_NOT_PRESENT ; 
 int /*<<< orphan*/  IXGBE_ERR_SFP_NOT_SUPPORTED ; 
#define  ixgbe_sfp_type_1g_cu_core0 141 
#define  ixgbe_sfp_type_1g_cu_core1 140 
#define  ixgbe_sfp_type_1g_lx_core0 139 
#define  ixgbe_sfp_type_1g_lx_core1 138 
#define  ixgbe_sfp_type_1g_sx_core0 137 
#define  ixgbe_sfp_type_1g_sx_core1 136 
#define  ixgbe_sfp_type_da_act_lmt_core0 135 
#define  ixgbe_sfp_type_da_act_lmt_core1 134 
#define  ixgbe_sfp_type_da_cu_core0 133 
#define  ixgbe_sfp_type_da_cu_core1 132 
#define  ixgbe_sfp_type_not_present 131 
#define  ixgbe_sfp_type_srlr_core0 130 
#define  ixgbe_sfp_type_srlr_core1 129 
#define  ixgbe_sfp_type_unknown 128 

__attribute__((used)) static s32 ixgbe_supported_sfp_modules_X550em(struct ixgbe_hw *hw, bool *linear)
{
	switch (hw->phy.sfp_type) {
	case ixgbe_sfp_type_not_present:
		return IXGBE_ERR_SFP_NOT_PRESENT;
	case ixgbe_sfp_type_da_cu_core0:
	case ixgbe_sfp_type_da_cu_core1:
		*linear = true;
		break;
	case ixgbe_sfp_type_srlr_core0:
	case ixgbe_sfp_type_srlr_core1:
	case ixgbe_sfp_type_da_act_lmt_core0:
	case ixgbe_sfp_type_da_act_lmt_core1:
	case ixgbe_sfp_type_1g_sx_core0:
	case ixgbe_sfp_type_1g_sx_core1:
	case ixgbe_sfp_type_1g_lx_core0:
	case ixgbe_sfp_type_1g_lx_core1:
		*linear = false;
		break;
	case ixgbe_sfp_type_unknown:
	case ixgbe_sfp_type_1g_cu_core0:
	case ixgbe_sfp_type_1g_cu_core1:
	default:
		return IXGBE_ERR_SFP_NOT_SUPPORTED;
	}

	return 0;
}