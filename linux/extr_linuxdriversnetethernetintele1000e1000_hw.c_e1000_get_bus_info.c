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
struct e1000_hw {int mac_type; void* bus_type; int /*<<< orphan*/  bus_width; void* bus_speed; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DEV_ID_82546EB_QUAD_COPPER ; 
 int E1000_STATUS_BUS64 ; 
 int E1000_STATUS_PCI66 ; 
 int E1000_STATUS_PCIX_MODE ; 
 int E1000_STATUS_PCIX_SPEED ; 
#define  E1000_STATUS_PCIX_SPEED_100 132 
#define  E1000_STATUS_PCIX_SPEED_133 131 
#define  E1000_STATUS_PCIX_SPEED_66 130 
 int /*<<< orphan*/  STATUS ; 
#define  e1000_82542_rev2_0 129 
#define  e1000_82542_rev2_1 128 
 void* e1000_bus_speed_100 ; 
 void* e1000_bus_speed_120 ; 
 void* e1000_bus_speed_133 ; 
 void* e1000_bus_speed_33 ; 
 void* e1000_bus_speed_66 ; 
 void* e1000_bus_speed_reserved ; 
 void* e1000_bus_speed_unknown ; 
 void* e1000_bus_type_pci ; 
 void* e1000_bus_type_pcix ; 
 int /*<<< orphan*/  e1000_bus_width_32 ; 
 int /*<<< orphan*/  e1000_bus_width_64 ; 
 int /*<<< orphan*/  e1000_bus_width_unknown ; 
 int er32 (int /*<<< orphan*/ ) ; 

void e1000_get_bus_info(struct e1000_hw *hw)
{
	u32 status;

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
		hw->bus_type = e1000_bus_type_pci;
		hw->bus_speed = e1000_bus_speed_unknown;
		hw->bus_width = e1000_bus_width_unknown;
		break;
	default:
		status = er32(STATUS);
		hw->bus_type = (status & E1000_STATUS_PCIX_MODE) ?
		    e1000_bus_type_pcix : e1000_bus_type_pci;

		if (hw->device_id == E1000_DEV_ID_82546EB_QUAD_COPPER) {
			hw->bus_speed = (hw->bus_type == e1000_bus_type_pci) ?
			    e1000_bus_speed_66 : e1000_bus_speed_120;
		} else if (hw->bus_type == e1000_bus_type_pci) {
			hw->bus_speed = (status & E1000_STATUS_PCI66) ?
			    e1000_bus_speed_66 : e1000_bus_speed_33;
		} else {
			switch (status & E1000_STATUS_PCIX_SPEED) {
			case E1000_STATUS_PCIX_SPEED_66:
				hw->bus_speed = e1000_bus_speed_66;
				break;
			case E1000_STATUS_PCIX_SPEED_100:
				hw->bus_speed = e1000_bus_speed_100;
				break;
			case E1000_STATUS_PCIX_SPEED_133:
				hw->bus_speed = e1000_bus_speed_133;
				break;
			default:
				hw->bus_speed = e1000_bus_speed_reserved;
				break;
			}
		}
		hw->bus_width = (status & E1000_STATUS_BUS64) ?
		    e1000_bus_width_64 : e1000_bus_width_32;
		break;
	}
}