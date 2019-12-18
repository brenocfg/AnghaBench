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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct i40e_hw {scalar_t__ vendor_id; int device_id; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
#define  I40E_DEV_ID_10G_B 150 
#define  I40E_DEV_ID_10G_BASE_T 149 
#define  I40E_DEV_ID_10G_BASE_T4 148 
#define  I40E_DEV_ID_10G_BASE_T_X722 147 
#define  I40E_DEV_ID_10G_SFP 146 
#define  I40E_DEV_ID_1G_BASE_T_X722 145 
#define  I40E_DEV_ID_20G_KR2 144 
#define  I40E_DEV_ID_20G_KR2_A 143 
#define  I40E_DEV_ID_25G_B 142 
#define  I40E_DEV_ID_25G_SFP28 141 
#define  I40E_DEV_ID_KX_B 140 
#define  I40E_DEV_ID_KX_C 139 
#define  I40E_DEV_ID_KX_X722 138 
#define  I40E_DEV_ID_QEMU 137 
#define  I40E_DEV_ID_QSFP_A 136 
#define  I40E_DEV_ID_QSFP_B 135 
#define  I40E_DEV_ID_QSFP_C 134 
#define  I40E_DEV_ID_QSFP_X722 133 
#define  I40E_DEV_ID_SFP_I_X722 132 
#define  I40E_DEV_ID_SFP_X722 131 
#define  I40E_DEV_ID_SFP_XL710 130 
#define  I40E_DEV_ID_X710_N3000 129 
#define  I40E_DEV_ID_XXV710_N3000 128 
 int /*<<< orphan*/  I40E_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  I40E_MAC_GENERIC ; 
 int /*<<< orphan*/  I40E_MAC_X722 ; 
 int /*<<< orphan*/  I40E_MAC_XL710 ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  hw_dbg (struct i40e_hw*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

i40e_status i40e_set_mac_type(struct i40e_hw *hw)
{
	i40e_status status = 0;

	if (hw->vendor_id == PCI_VENDOR_ID_INTEL) {
		switch (hw->device_id) {
		case I40E_DEV_ID_SFP_XL710:
		case I40E_DEV_ID_QEMU:
		case I40E_DEV_ID_KX_B:
		case I40E_DEV_ID_KX_C:
		case I40E_DEV_ID_QSFP_A:
		case I40E_DEV_ID_QSFP_B:
		case I40E_DEV_ID_QSFP_C:
		case I40E_DEV_ID_10G_BASE_T:
		case I40E_DEV_ID_10G_BASE_T4:
		case I40E_DEV_ID_10G_B:
		case I40E_DEV_ID_10G_SFP:
		case I40E_DEV_ID_20G_KR2:
		case I40E_DEV_ID_20G_KR2_A:
		case I40E_DEV_ID_25G_B:
		case I40E_DEV_ID_25G_SFP28:
		case I40E_DEV_ID_X710_N3000:
		case I40E_DEV_ID_XXV710_N3000:
			hw->mac.type = I40E_MAC_XL710;
			break;
		case I40E_DEV_ID_KX_X722:
		case I40E_DEV_ID_QSFP_X722:
		case I40E_DEV_ID_SFP_X722:
		case I40E_DEV_ID_1G_BASE_T_X722:
		case I40E_DEV_ID_10G_BASE_T_X722:
		case I40E_DEV_ID_SFP_I_X722:
			hw->mac.type = I40E_MAC_X722;
			break;
		default:
			hw->mac.type = I40E_MAC_GENERIC;
			break;
		}
	} else {
		status = I40E_ERR_DEVICE_NOT_SUPPORTED;
	}

	hw_dbg(hw, "i40e_set_mac_type found mac: %d, returns: %d\n",
		  hw->mac.type, status);
	return status;
}