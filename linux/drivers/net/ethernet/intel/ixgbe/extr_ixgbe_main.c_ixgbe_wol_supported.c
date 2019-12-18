#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ func; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ bus; TYPE_2__ mac; } ;
struct ixgbe_adapter {scalar_t__ eeprom_cap; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_DEVICE_CAPS_WOL_MASK ; 
 scalar_t__ IXGBE_DEVICE_CAPS_WOL_PORT0 ; 
 scalar_t__ IXGBE_DEVICE_CAPS_WOL_PORT0_1 ; 
#define  IXGBE_DEV_ID_82599EN_SFP 143 
#define  IXGBE_DEV_ID_82599_COMBO_BACKPLANE 142 
#define  IXGBE_DEV_ID_82599_KX4 141 
#define  IXGBE_DEV_ID_82599_SFP 140 
#define  IXGBE_SUBDEV_ID_82599EN_SFP_OCP1 139 
#define  IXGBE_SUBDEV_ID_82599_560FLR 138 
#define  IXGBE_SUBDEV_ID_82599_ECNA_DP 137 
 scalar_t__ IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ ; 
#define  IXGBE_SUBDEV_ID_82599_LOM_SNAP6 136 
#define  IXGBE_SUBDEV_ID_82599_RNDC 135 
#define  IXGBE_SUBDEV_ID_82599_SFP 134 
#define  IXGBE_SUBDEV_ID_82599_SFP_1OCP 133 
#define  IXGBE_SUBDEV_ID_82599_SFP_2OCP 132 
#define  IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM1 131 
#define  IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM2 130 
#define  IXGBE_SUBDEV_ID_82599_SFP_WOL0 129 
#define  IXGBE_SUBDEV_ID_82599_SP_560FLR 128 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_X540 ; 

bool ixgbe_wol_supported(struct ixgbe_adapter *adapter, u16 device_id,
			 u16 subdevice_id)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u16 wol_cap = adapter->eeprom_cap & IXGBE_DEVICE_CAPS_WOL_MASK;

	/* WOL not supported on 82598 */
	if (hw->mac.type == ixgbe_mac_82598EB)
		return false;

	/* check eeprom to see if WOL is enabled for X540 and newer */
	if (hw->mac.type >= ixgbe_mac_X540) {
		if ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0_1) ||
		    ((wol_cap == IXGBE_DEVICE_CAPS_WOL_PORT0) &&
		     (hw->bus.func == 0)))
			return true;
	}

	/* WOL is determined based on device IDs for 82599 MACs */
	switch (device_id) {
	case IXGBE_DEV_ID_82599_SFP:
		/* Only these subdevices could supports WOL */
		switch (subdevice_id) {
		case IXGBE_SUBDEV_ID_82599_560FLR:
		case IXGBE_SUBDEV_ID_82599_LOM_SNAP6:
		case IXGBE_SUBDEV_ID_82599_SFP_WOL0:
		case IXGBE_SUBDEV_ID_82599_SFP_2OCP:
			/* only support first port */
			if (hw->bus.func != 0)
				break;
			/* fall through */
		case IXGBE_SUBDEV_ID_82599_SP_560FLR:
		case IXGBE_SUBDEV_ID_82599_SFP:
		case IXGBE_SUBDEV_ID_82599_RNDC:
		case IXGBE_SUBDEV_ID_82599_ECNA_DP:
		case IXGBE_SUBDEV_ID_82599_SFP_1OCP:
		case IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM1:
		case IXGBE_SUBDEV_ID_82599_SFP_LOM_OEM2:
			return true;
		}
		break;
	case IXGBE_DEV_ID_82599EN_SFP:
		/* Only these subdevices support WOL */
		switch (subdevice_id) {
		case IXGBE_SUBDEV_ID_82599EN_SFP_OCP1:
			return true;
		}
		break;
	case IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
		/* All except this subdevice support WOL */
		if (subdevice_id != IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ)
			return true;
		break;
	case IXGBE_DEV_ID_82599_KX4:
		return  true;
	default:
		break;
	}

	return false;
}