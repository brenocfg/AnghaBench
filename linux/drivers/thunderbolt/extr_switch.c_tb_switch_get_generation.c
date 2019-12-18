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
struct TYPE_2__ {int device_id; } ;
struct tb_switch {TYPE_1__ config; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE 148 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE 147 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE 146 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE 145 
#define  PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE 144 
#define  PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_2C 143 
#define  PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C 142 
#define  PCI_DEVICE_ID_INTEL_EAGLE_RIDGE 141 
#define  PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_BRIDGE 140 
#define  PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_BRIDGE 139 
#define  PCI_DEVICE_ID_INTEL_ICL_NHI0 138 
#define  PCI_DEVICE_ID_INTEL_ICL_NHI1 137 
#define  PCI_DEVICE_ID_INTEL_LIGHT_PEAK 136 
#define  PCI_DEVICE_ID_INTEL_LIGHT_RIDGE 135 
#define  PCI_DEVICE_ID_INTEL_PORT_RIDGE 134 
#define  PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_2C_BRIDGE 133 
#define  PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_4C_BRIDGE 132 
#define  PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE 131 
#define  PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE 130 
#define  PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_BRIDGE 129 
#define  PCI_DEVICE_ID_INTEL_WIN_RIDGE_2C_BRIDGE 128 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*,int) ; 

__attribute__((used)) static int tb_switch_get_generation(struct tb_switch *sw)
{
	switch (sw->config.device_id) {
	case PCI_DEVICE_ID_INTEL_LIGHT_RIDGE:
	case PCI_DEVICE_ID_INTEL_EAGLE_RIDGE:
	case PCI_DEVICE_ID_INTEL_LIGHT_PEAK:
	case PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_2C:
	case PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C:
	case PCI_DEVICE_ID_INTEL_PORT_RIDGE:
	case PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_REDWOOD_RIDGE_4C_BRIDGE:
		return 1;

	case PCI_DEVICE_ID_INTEL_WIN_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_BRIDGE:
		return 2;

	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE:
	case PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_BRIDGE:
	case PCI_DEVICE_ID_INTEL_ICL_NHI0:
	case PCI_DEVICE_ID_INTEL_ICL_NHI1:
		return 3;

	default:
		/*
		 * For unknown switches assume generation to be 1 to be
		 * on the safe side.
		 */
		tb_sw_warn(sw, "unsupported switch device id %#x\n",
			   sw->config.device_id);
		return 1;
	}
}