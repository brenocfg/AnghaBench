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
struct ethtool_wolinfo {int /*<<< orphan*/  supported; } ;
struct e1000_hw {int device_id; } ;
struct e1000_adapter {int /*<<< orphan*/  eeprom_wol; int /*<<< orphan*/  quad_port_a; struct e1000_hw hw; } ;

/* Variables and functions */
#define  E1000_DEV_ID_82542 139 
#define  E1000_DEV_ID_82543GC_COPPER 138 
#define  E1000_DEV_ID_82543GC_FIBER 137 
#define  E1000_DEV_ID_82544EI_FIBER 136 
#define  E1000_DEV_ID_82545EM_COPPER 135 
#define  E1000_DEV_ID_82545EM_FIBER 134 
#define  E1000_DEV_ID_82546EB_FIBER 133 
#define  E1000_DEV_ID_82546EB_QUAD_COPPER 132 
#define  E1000_DEV_ID_82546GB_FIBER 131 
#define  E1000_DEV_ID_82546GB_PCIE 130 
#define  E1000_DEV_ID_82546GB_QUAD_COPPER 129 
#define  E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 128 
 int E1000_STATUS_FUNC_1 ; 
 int /*<<< orphan*/  STATUS ; 
 int er32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_wol_exclusion(struct e1000_adapter *adapter,
			       struct ethtool_wolinfo *wol)
{
	struct e1000_hw *hw = &adapter->hw;
	int retval = 1; /* fail by default */

	switch (hw->device_id) {
	case E1000_DEV_ID_82542:
	case E1000_DEV_ID_82543GC_FIBER:
	case E1000_DEV_ID_82543GC_COPPER:
	case E1000_DEV_ID_82544EI_FIBER:
	case E1000_DEV_ID_82546EB_QUAD_COPPER:
	case E1000_DEV_ID_82545EM_FIBER:
	case E1000_DEV_ID_82545EM_COPPER:
	case E1000_DEV_ID_82546GB_QUAD_COPPER:
	case E1000_DEV_ID_82546GB_PCIE:
		/* these don't support WoL at all */
		wol->supported = 0;
		break;
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546GB_FIBER:
		/* Wake events not supported on port B */
		if (er32(STATUS) & E1000_STATUS_FUNC_1) {
			wol->supported = 0;
			break;
		}
		/* return success for non excluded adapter ports */
		retval = 0;
		break;
	case E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* quad port adapters only support WoL on port A */
		if (!adapter->quad_port_a) {
			wol->supported = 0;
			break;
		}
		/* return success for non excluded adapter ports */
		retval = 0;
		break;
	default:
		/* dual port cards only support WoL on port A from now on
		 * unless it was enabled in the eeprom for port B
		 * so exclude FUNC_1 ports from having WoL enabled
		 */
		if (er32(STATUS) & E1000_STATUS_FUNC_1 &&
		    !adapter->eeprom_wol) {
			wol->supported = 0;
			break;
		}

		retval = 0;
	}

	return retval;
}