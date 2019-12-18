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
typedef  enum ixgbe_bus_speed { ____Placeholder_ixgbe_bus_speed } ixgbe_bus_speed ;

/* Variables and functions */
 int IXGBE_PCI_LINK_SPEED ; 
#define  IXGBE_PCI_LINK_SPEED_2500 130 
#define  IXGBE_PCI_LINK_SPEED_5000 129 
#define  IXGBE_PCI_LINK_SPEED_8000 128 
 int ixgbe_bus_speed_2500 ; 
 int ixgbe_bus_speed_5000 ; 
 int ixgbe_bus_speed_8000 ; 
 int ixgbe_bus_speed_unknown ; 

enum ixgbe_bus_speed ixgbe_convert_bus_speed(u16 link_status)
{
	switch (link_status & IXGBE_PCI_LINK_SPEED) {
	case IXGBE_PCI_LINK_SPEED_2500:
		return ixgbe_bus_speed_2500;
	case IXGBE_PCI_LINK_SPEED_5000:
		return ixgbe_bus_speed_5000;
	case IXGBE_PCI_LINK_SPEED_8000:
		return ixgbe_bus_speed_8000;
	default:
		return ixgbe_bus_speed_unknown;
	}
}