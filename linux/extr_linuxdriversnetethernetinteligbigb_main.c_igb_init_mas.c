#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int func; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ bus; TYPE_2__ nvm; } ;
struct igb_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; struct e1000_hw hw; } ;

/* Variables and functions */
#define  E1000_FUNC_0 131 
#define  E1000_FUNC_1 130 
#define  E1000_FUNC_2 129 
#define  E1000_FUNC_3 128 
 int /*<<< orphan*/  IGB_FLAG_MAS_ENABLE ; 
 int IGB_MAS_ENABLE_0 ; 
 int IGB_MAS_ENABLE_1 ; 
 int IGB_MAS_ENABLE_2 ; 
 int IGB_MAS_ENABLE_3 ; 
 int /*<<< orphan*/  NVM_COMPAT ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void igb_init_mas(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 eeprom_data;

	hw->nvm.ops.read(hw, NVM_COMPAT, 1, &eeprom_data);
	switch (hw->bus.func) {
	case E1000_FUNC_0:
		if (eeprom_data & IGB_MAS_ENABLE_0) {
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		}
		break;
	case E1000_FUNC_1:
		if (eeprom_data & IGB_MAS_ENABLE_1) {
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		}
		break;
	case E1000_FUNC_2:
		if (eeprom_data & IGB_MAS_ENABLE_2) {
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		}
		break;
	case E1000_FUNC_3:
		if (eeprom_data & IGB_MAS_ENABLE_3) {
			adapter->flags |= IGB_FLAG_MAS_ENABLE;
			netdev_info(adapter->netdev,
				"MAS: Enabling Media Autosense for port %d\n",
				hw->bus.func);
		}
		break;
	default:
		/* Shouldn't get here */
		netdev_err(adapter->netdev,
			"MAS: Invalid port configuration, returning\n");
		break;
	}
}