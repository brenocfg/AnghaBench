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
struct igc_mac_info {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  media_type; } ;
struct igc_hw {int device_id; struct igc_mac_info mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  IGC_DEV_ID_I220_V 133 
#define  IGC_DEV_ID_I225_I 132 
#define  IGC_DEV_ID_I225_K 131 
#define  IGC_DEV_ID_I225_LM 130 
#define  IGC_DEV_ID_I225_V 129 
 scalar_t__ IGC_ERR_MAC_INIT ; 
#define  igc_i225 128 
 scalar_t__ igc_init_mac_params_base (struct igc_hw*) ; 
 scalar_t__ igc_init_nvm_params_base (struct igc_hw*) ; 
 scalar_t__ igc_init_nvm_params_i225 (struct igc_hw*) ; 
 scalar_t__ igc_init_phy_params_base (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_media_type_copper ; 

__attribute__((used)) static s32 igc_get_invariants_base(struct igc_hw *hw)
{
	struct igc_mac_info *mac = &hw->mac;
	s32 ret_val = 0;

	switch (hw->device_id) {
	case IGC_DEV_ID_I225_LM:
	case IGC_DEV_ID_I225_V:
	case IGC_DEV_ID_I225_I:
	case IGC_DEV_ID_I220_V:
	case IGC_DEV_ID_I225_K:
		mac->type = igc_i225;
		break;
	default:
		return -IGC_ERR_MAC_INIT;
	}

	hw->phy.media_type = igc_media_type_copper;

	/* mac initialization and operations */
	ret_val = igc_init_mac_params_base(hw);
	if (ret_val)
		goto out;

	/* NVM initialization */
	ret_val = igc_init_nvm_params_base(hw);
	switch (hw->mac.type) {
	case igc_i225:
		ret_val = igc_init_nvm_params_i225(hw);
		break;
	default:
		break;
	}

	/* setup PHY parameters */
	ret_val = igc_init_phy_params_base(hw);
	if (ret_val)
		goto out;

out:
	return ret_val;
}