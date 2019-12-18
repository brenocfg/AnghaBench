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
typedef  int u16 ;
typedef  enum ixgbe_bus_width { ____Placeholder_ixgbe_bus_width } ixgbe_bus_width ;

/* Variables and functions */
 int IXGBE_PCI_LINK_WIDTH ; 
#define  IXGBE_PCI_LINK_WIDTH_1 131 
#define  IXGBE_PCI_LINK_WIDTH_2 130 
#define  IXGBE_PCI_LINK_WIDTH_4 129 
#define  IXGBE_PCI_LINK_WIDTH_8 128 
 int ixgbe_bus_width_pcie_x1 ; 
 int ixgbe_bus_width_pcie_x2 ; 
 int ixgbe_bus_width_pcie_x4 ; 
 int ixgbe_bus_width_pcie_x8 ; 
 int ixgbe_bus_width_unknown ; 

enum ixgbe_bus_width ixgbe_convert_bus_width(u16 link_status)
{
	switch (link_status & IXGBE_PCI_LINK_WIDTH) {
	case IXGBE_PCI_LINK_WIDTH_1:
		return ixgbe_bus_width_pcie_x1;
	case IXGBE_PCI_LINK_WIDTH_2:
		return ixgbe_bus_width_pcie_x2;
	case IXGBE_PCI_LINK_WIDTH_4:
		return ixgbe_bus_width_pcie_x4;
	case IXGBE_PCI_LINK_WIDTH_8:
		return ixgbe_bus_width_pcie_x8;
	default:
		return ixgbe_bus_width_unknown;
	}
}