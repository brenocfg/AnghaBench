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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  width; int /*<<< orphan*/  type; } ;
struct i40e_hw {TYPE_1__ bus; } ;

/* Variables and functions */
 int PCI_EXP_LNKSTA_CLS ; 
#define  PCI_EXP_LNKSTA_CLS_2_5GB 134 
#define  PCI_EXP_LNKSTA_CLS_5_0GB 133 
#define  PCI_EXP_LNKSTA_CLS_8_0GB 132 
 int PCI_EXP_LNKSTA_NLW ; 
#define  PCI_EXP_LNKSTA_NLW_X1 131 
#define  PCI_EXP_LNKSTA_NLW_X2 130 
#define  PCI_EXP_LNKSTA_NLW_X4 129 
#define  PCI_EXP_LNKSTA_NLW_X8 128 
 int /*<<< orphan*/  i40e_bus_speed_2500 ; 
 int /*<<< orphan*/  i40e_bus_speed_5000 ; 
 int /*<<< orphan*/  i40e_bus_speed_8000 ; 
 int /*<<< orphan*/  i40e_bus_speed_unknown ; 
 int /*<<< orphan*/  i40e_bus_type_pci_express ; 
 int /*<<< orphan*/  i40e_bus_width_pcie_x1 ; 
 int /*<<< orphan*/  i40e_bus_width_pcie_x2 ; 
 int /*<<< orphan*/  i40e_bus_width_pcie_x4 ; 
 int /*<<< orphan*/  i40e_bus_width_pcie_x8 ; 
 int /*<<< orphan*/  i40e_bus_width_unknown ; 

void i40e_set_pci_config_data(struct i40e_hw *hw, u16 link_status)
{
	hw->bus.type = i40e_bus_type_pci_express;

	switch (link_status & PCI_EXP_LNKSTA_NLW) {
	case PCI_EXP_LNKSTA_NLW_X1:
		hw->bus.width = i40e_bus_width_pcie_x1;
		break;
	case PCI_EXP_LNKSTA_NLW_X2:
		hw->bus.width = i40e_bus_width_pcie_x2;
		break;
	case PCI_EXP_LNKSTA_NLW_X4:
		hw->bus.width = i40e_bus_width_pcie_x4;
		break;
	case PCI_EXP_LNKSTA_NLW_X8:
		hw->bus.width = i40e_bus_width_pcie_x8;
		break;
	default:
		hw->bus.width = i40e_bus_width_unknown;
		break;
	}

	switch (link_status & PCI_EXP_LNKSTA_CLS) {
	case PCI_EXP_LNKSTA_CLS_2_5GB:
		hw->bus.speed = i40e_bus_speed_2500;
		break;
	case PCI_EXP_LNKSTA_CLS_5_0GB:
		hw->bus.speed = i40e_bus_speed_5000;
		break;
	case PCI_EXP_LNKSTA_CLS_8_0GB:
		hw->bus.speed = i40e_bus_speed_8000;
		break;
	default:
		hw->bus.speed = i40e_bus_speed_unknown;
		break;
	}
}