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
typedef  int u16 ;
struct TYPE_4__ {void* payload; void* speed; void* width; } ;
struct TYPE_3__ {void* payload; void* speed; void* width; } ;
struct fm10k_hw {TYPE_2__ bus; TYPE_1__ bus_caps; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_PCIE_DEV_CAP ; 
 int FM10K_PCIE_DEV_CAP_PAYLOAD ; 
#define  FM10K_PCIE_DEV_CAP_PAYLOAD_128 140 
#define  FM10K_PCIE_DEV_CAP_PAYLOAD_256 139 
#define  FM10K_PCIE_DEV_CAP_PAYLOAD_512 138 
 int /*<<< orphan*/  FM10K_PCIE_DEV_CTRL ; 
 int FM10K_PCIE_DEV_CTRL_PAYLOAD ; 
#define  FM10K_PCIE_DEV_CTRL_PAYLOAD_128 137 
#define  FM10K_PCIE_DEV_CTRL_PAYLOAD_256 136 
#define  FM10K_PCIE_DEV_CTRL_PAYLOAD_512 135 
 int /*<<< orphan*/  FM10K_PCIE_LINK_CAP ; 
 int FM10K_PCIE_LINK_SPEED ; 
#define  FM10K_PCIE_LINK_SPEED_2500 134 
#define  FM10K_PCIE_LINK_SPEED_5000 133 
#define  FM10K_PCIE_LINK_SPEED_8000 132 
 int /*<<< orphan*/  FM10K_PCIE_LINK_STATUS ; 
 int FM10K_PCIE_LINK_WIDTH ; 
#define  FM10K_PCIE_LINK_WIDTH_1 131 
#define  FM10K_PCIE_LINK_WIDTH_2 130 
#define  FM10K_PCIE_LINK_WIDTH_4 129 
#define  FM10K_PCIE_LINK_WIDTH_8 128 
 void* fm10k_bus_payload_128 ; 
 void* fm10k_bus_payload_256 ; 
 void* fm10k_bus_payload_512 ; 
 void* fm10k_bus_payload_unknown ; 
 void* fm10k_bus_speed_2500 ; 
 void* fm10k_bus_speed_5000 ; 
 void* fm10k_bus_speed_8000 ; 
 void* fm10k_bus_speed_unknown ; 
 void* fm10k_bus_width_pcie_x1 ; 
 void* fm10k_bus_width_pcie_x2 ; 
 void* fm10k_bus_width_pcie_x4 ; 
 void* fm10k_bus_width_pcie_x8 ; 
 void* fm10k_bus_width_unknown ; 
 int fm10k_read_pci_cfg_word (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

s32 fm10k_get_bus_info_generic(struct fm10k_hw *hw)
{
	u16 link_cap, link_status, device_cap, device_control;

	/* Get the maximum link width and speed from PCIe config space */
	link_cap = fm10k_read_pci_cfg_word(hw, FM10K_PCIE_LINK_CAP);

	switch (link_cap & FM10K_PCIE_LINK_WIDTH) {
	case FM10K_PCIE_LINK_WIDTH_1:
		hw->bus_caps.width = fm10k_bus_width_pcie_x1;
		break;
	case FM10K_PCIE_LINK_WIDTH_2:
		hw->bus_caps.width = fm10k_bus_width_pcie_x2;
		break;
	case FM10K_PCIE_LINK_WIDTH_4:
		hw->bus_caps.width = fm10k_bus_width_pcie_x4;
		break;
	case FM10K_PCIE_LINK_WIDTH_8:
		hw->bus_caps.width = fm10k_bus_width_pcie_x8;
		break;
	default:
		hw->bus_caps.width = fm10k_bus_width_unknown;
		break;
	}

	switch (link_cap & FM10K_PCIE_LINK_SPEED) {
	case FM10K_PCIE_LINK_SPEED_2500:
		hw->bus_caps.speed = fm10k_bus_speed_2500;
		break;
	case FM10K_PCIE_LINK_SPEED_5000:
		hw->bus_caps.speed = fm10k_bus_speed_5000;
		break;
	case FM10K_PCIE_LINK_SPEED_8000:
		hw->bus_caps.speed = fm10k_bus_speed_8000;
		break;
	default:
		hw->bus_caps.speed = fm10k_bus_speed_unknown;
		break;
	}

	/* Get the PCIe maximum payload size for the PCIe function */
	device_cap = fm10k_read_pci_cfg_word(hw, FM10K_PCIE_DEV_CAP);

	switch (device_cap & FM10K_PCIE_DEV_CAP_PAYLOAD) {
	case FM10K_PCIE_DEV_CAP_PAYLOAD_128:
		hw->bus_caps.payload = fm10k_bus_payload_128;
		break;
	case FM10K_PCIE_DEV_CAP_PAYLOAD_256:
		hw->bus_caps.payload = fm10k_bus_payload_256;
		break;
	case FM10K_PCIE_DEV_CAP_PAYLOAD_512:
		hw->bus_caps.payload = fm10k_bus_payload_512;
		break;
	default:
		hw->bus_caps.payload = fm10k_bus_payload_unknown;
		break;
	}

	/* Get the negotiated link width and speed from PCIe config space */
	link_status = fm10k_read_pci_cfg_word(hw, FM10K_PCIE_LINK_STATUS);

	switch (link_status & FM10K_PCIE_LINK_WIDTH) {
	case FM10K_PCIE_LINK_WIDTH_1:
		hw->bus.width = fm10k_bus_width_pcie_x1;
		break;
	case FM10K_PCIE_LINK_WIDTH_2:
		hw->bus.width = fm10k_bus_width_pcie_x2;
		break;
	case FM10K_PCIE_LINK_WIDTH_4:
		hw->bus.width = fm10k_bus_width_pcie_x4;
		break;
	case FM10K_PCIE_LINK_WIDTH_8:
		hw->bus.width = fm10k_bus_width_pcie_x8;
		break;
	default:
		hw->bus.width = fm10k_bus_width_unknown;
		break;
	}

	switch (link_status & FM10K_PCIE_LINK_SPEED) {
	case FM10K_PCIE_LINK_SPEED_2500:
		hw->bus.speed = fm10k_bus_speed_2500;
		break;
	case FM10K_PCIE_LINK_SPEED_5000:
		hw->bus.speed = fm10k_bus_speed_5000;
		break;
	case FM10K_PCIE_LINK_SPEED_8000:
		hw->bus.speed = fm10k_bus_speed_8000;
		break;
	default:
		hw->bus.speed = fm10k_bus_speed_unknown;
		break;
	}

	/* Get the negotiated PCIe maximum payload size for the PCIe function */
	device_control = fm10k_read_pci_cfg_word(hw, FM10K_PCIE_DEV_CTRL);

	switch (device_control & FM10K_PCIE_DEV_CTRL_PAYLOAD) {
	case FM10K_PCIE_DEV_CTRL_PAYLOAD_128:
		hw->bus.payload = fm10k_bus_payload_128;
		break;
	case FM10K_PCIE_DEV_CTRL_PAYLOAD_256:
		hw->bus.payload = fm10k_bus_payload_256;
		break;
	case FM10K_PCIE_DEV_CTRL_PAYLOAD_512:
		hw->bus.payload = fm10k_bus_payload_512;
		break;
	default:
		hw->bus.payload = fm10k_bus_payload_unknown;
		break;
	}

	return 0;
}