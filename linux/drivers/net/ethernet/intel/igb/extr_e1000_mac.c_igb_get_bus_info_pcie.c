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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_bus_info {int width; int func; void* speed; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_bus_info bus; } ;
typedef  scalar_t__ s32 ;
typedef  enum e1000_bus_width { ____Placeholder_e1000_bus_width } e1000_bus_width ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_FUNC_MASK ; 
 int E1000_STATUS_FUNC_SHIFT ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_CLS ; 
#define  PCI_EXP_LNKSTA_CLS_2_5GB 129 
#define  PCI_EXP_LNKSTA_CLS_5_0GB 128 
 int PCI_EXP_LNKSTA_NLW ; 
 int PCI_EXP_LNKSTA_NLW_SHIFT ; 
 void* e1000_bus_speed_2500 ; 
 void* e1000_bus_speed_5000 ; 
 void* e1000_bus_speed_unknown ; 
 int /*<<< orphan*/  e1000_bus_type_pci_express ; 
 int e1000_bus_width_unknown ; 
 scalar_t__ igb_read_pcie_cap_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 

s32 igb_get_bus_info_pcie(struct e1000_hw *hw)
{
	struct e1000_bus_info *bus = &hw->bus;
	s32 ret_val;
	u32 reg;
	u16 pcie_link_status;

	bus->type = e1000_bus_type_pci_express;

	ret_val = igb_read_pcie_cap_reg(hw,
					PCI_EXP_LNKSTA,
					&pcie_link_status);
	if (ret_val) {
		bus->width = e1000_bus_width_unknown;
		bus->speed = e1000_bus_speed_unknown;
	} else {
		switch (pcie_link_status & PCI_EXP_LNKSTA_CLS) {
		case PCI_EXP_LNKSTA_CLS_2_5GB:
			bus->speed = e1000_bus_speed_2500;
			break;
		case PCI_EXP_LNKSTA_CLS_5_0GB:
			bus->speed = e1000_bus_speed_5000;
			break;
		default:
			bus->speed = e1000_bus_speed_unknown;
			break;
		}

		bus->width = (enum e1000_bus_width)((pcie_link_status &
						     PCI_EXP_LNKSTA_NLW) >>
						     PCI_EXP_LNKSTA_NLW_SHIFT);
	}

	reg = rd32(E1000_STATUS);
	bus->func = (reg & E1000_STATUS_FUNC_MASK) >> E1000_STATUS_FUNC_SHIFT;

	return 0;
}