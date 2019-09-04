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
struct e1000_hw {int device_id; int mac_type; int asf_firmware_present; int bad_tx_carr_stats_fd; int has_smbus; int /*<<< orphan*/  revision_id; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  E1000_82542_2_0_REV_ID 170 
#define  E1000_82542_2_1_REV_ID 169 
#define  E1000_DEV_ID_82540EM 168 
#define  E1000_DEV_ID_82540EM_LOM 167 
#define  E1000_DEV_ID_82540EP 166 
#define  E1000_DEV_ID_82540EP_LOM 165 
#define  E1000_DEV_ID_82540EP_LP 164 
#define  E1000_DEV_ID_82541EI 163 
#define  E1000_DEV_ID_82541EI_MOBILE 162 
#define  E1000_DEV_ID_82541ER 161 
#define  E1000_DEV_ID_82541ER_LOM 160 
#define  E1000_DEV_ID_82541GI 159 
#define  E1000_DEV_ID_82541GI_LF 158 
#define  E1000_DEV_ID_82541GI_MOBILE 157 
#define  E1000_DEV_ID_82542 156 
#define  E1000_DEV_ID_82543GC_COPPER 155 
#define  E1000_DEV_ID_82543GC_FIBER 154 
#define  E1000_DEV_ID_82544EI_COPPER 153 
#define  E1000_DEV_ID_82544EI_FIBER 152 
#define  E1000_DEV_ID_82544GC_COPPER 151 
#define  E1000_DEV_ID_82544GC_LOM 150 
#define  E1000_DEV_ID_82545EM_COPPER 149 
#define  E1000_DEV_ID_82545EM_FIBER 148 
#define  E1000_DEV_ID_82545GM_COPPER 147 
#define  E1000_DEV_ID_82545GM_FIBER 146 
#define  E1000_DEV_ID_82545GM_SERDES 145 
#define  E1000_DEV_ID_82546EB_COPPER 144 
#define  E1000_DEV_ID_82546EB_FIBER 143 
#define  E1000_DEV_ID_82546EB_QUAD_COPPER 142 
#define  E1000_DEV_ID_82546GB_COPPER 141 
#define  E1000_DEV_ID_82546GB_FIBER 140 
#define  E1000_DEV_ID_82546GB_PCIE 139 
#define  E1000_DEV_ID_82546GB_QUAD_COPPER 138 
#define  E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 137 
#define  E1000_DEV_ID_82546GB_SERDES 136 
#define  E1000_DEV_ID_82547EI 135 
#define  E1000_DEV_ID_82547EI_MOBILE 134 
#define  E1000_DEV_ID_82547GI 133 
#define  E1000_DEV_ID_INTEL_CE4100_GBE 132 
 int /*<<< orphan*/  E1000_ERR_MAC_TYPE ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int e1000_82540 ; 
#define  e1000_82541 131 
#define  e1000_82541_rev_2 130 
 int e1000_82542_rev2_0 ; 
 int e1000_82542_rev2_1 ; 
 int e1000_82543 ; 
 int e1000_82544 ; 
 int e1000_82545 ; 
 int e1000_82545_rev_3 ; 
 int e1000_82546 ; 
 int e1000_82546_rev_3 ; 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int e1000_ce4100 ; 

s32 e1000_set_mac_type(struct e1000_hw *hw)
{
	switch (hw->device_id) {
	case E1000_DEV_ID_82542:
		switch (hw->revision_id) {
		case E1000_82542_2_0_REV_ID:
			hw->mac_type = e1000_82542_rev2_0;
			break;
		case E1000_82542_2_1_REV_ID:
			hw->mac_type = e1000_82542_rev2_1;
			break;
		default:
			/* Invalid 82542 revision ID */
			return -E1000_ERR_MAC_TYPE;
		}
		break;
	case E1000_DEV_ID_82543GC_FIBER:
	case E1000_DEV_ID_82543GC_COPPER:
		hw->mac_type = e1000_82543;
		break;
	case E1000_DEV_ID_82544EI_COPPER:
	case E1000_DEV_ID_82544EI_FIBER:
	case E1000_DEV_ID_82544GC_COPPER:
	case E1000_DEV_ID_82544GC_LOM:
		hw->mac_type = e1000_82544;
		break;
	case E1000_DEV_ID_82540EM:
	case E1000_DEV_ID_82540EM_LOM:
	case E1000_DEV_ID_82540EP:
	case E1000_DEV_ID_82540EP_LOM:
	case E1000_DEV_ID_82540EP_LP:
		hw->mac_type = e1000_82540;
		break;
	case E1000_DEV_ID_82545EM_COPPER:
	case E1000_DEV_ID_82545EM_FIBER:
		hw->mac_type = e1000_82545;
		break;
	case E1000_DEV_ID_82545GM_COPPER:
	case E1000_DEV_ID_82545GM_FIBER:
	case E1000_DEV_ID_82545GM_SERDES:
		hw->mac_type = e1000_82545_rev_3;
		break;
	case E1000_DEV_ID_82546EB_COPPER:
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546EB_QUAD_COPPER:
		hw->mac_type = e1000_82546;
		break;
	case E1000_DEV_ID_82546GB_COPPER:
	case E1000_DEV_ID_82546GB_FIBER:
	case E1000_DEV_ID_82546GB_SERDES:
	case E1000_DEV_ID_82546GB_PCIE:
	case E1000_DEV_ID_82546GB_QUAD_COPPER:
	case E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		hw->mac_type = e1000_82546_rev_3;
		break;
	case E1000_DEV_ID_82541EI:
	case E1000_DEV_ID_82541EI_MOBILE:
	case E1000_DEV_ID_82541ER_LOM:
		hw->mac_type = e1000_82541;
		break;
	case E1000_DEV_ID_82541ER:
	case E1000_DEV_ID_82541GI:
	case E1000_DEV_ID_82541GI_LF:
	case E1000_DEV_ID_82541GI_MOBILE:
		hw->mac_type = e1000_82541_rev_2;
		break;
	case E1000_DEV_ID_82547EI:
	case E1000_DEV_ID_82547EI_MOBILE:
		hw->mac_type = e1000_82547;
		break;
	case E1000_DEV_ID_82547GI:
		hw->mac_type = e1000_82547_rev_2;
		break;
	case E1000_DEV_ID_INTEL_CE4100_GBE:
		hw->mac_type = e1000_ce4100;
		break;
	default:
		/* Should never have loaded on this device */
		return -E1000_ERR_MAC_TYPE;
	}

	switch (hw->mac_type) {
	case e1000_82541:
	case e1000_82547:
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		hw->asf_firmware_present = true;
		break;
	default:
		break;
	}

	/* The 82543 chip does not count tx_carrier_errors properly in
	 * FD mode
	 */
	if (hw->mac_type == e1000_82543)
		hw->bad_tx_carr_stats_fd = true;

	if (hw->mac_type > e1000_82544)
		hw->has_smbus = true;

	return E1000_SUCCESS;
}