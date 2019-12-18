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

/* Variables and functions */
#define  P5_DISABLED 131 
#define  P5_INTF_SEL_GMAC5 130 
#define  P5_INTF_SEL_PHY_P0 129 
#define  P5_INTF_SEL_PHY_P4 128 

__attribute__((used)) static const char *p5_intf_modes(unsigned int p5_interface)
{
	switch (p5_interface) {
	case P5_DISABLED:
		return "DISABLED";
	case P5_INTF_SEL_PHY_P0:
		return "PHY P0";
	case P5_INTF_SEL_PHY_P4:
		return "PHY P4";
	case P5_INTF_SEL_GMAC5:
		return "GMAC5";
	default:
		return "unknown";
	}
}