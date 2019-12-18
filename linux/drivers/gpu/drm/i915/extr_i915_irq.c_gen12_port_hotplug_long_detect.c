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
typedef  enum hpd_pin { ____Placeholder_hpd_pin } hpd_pin ;

/* Variables and functions */
 int GEN11_HOTPLUG_CTL_LONG_DETECT (int /*<<< orphan*/ ) ; 
#define  HPD_PORT_D 133 
#define  HPD_PORT_E 132 
#define  HPD_PORT_F 131 
#define  HPD_PORT_G 130 
#define  HPD_PORT_H 129 
#define  HPD_PORT_I 128 
 int /*<<< orphan*/  PORT_TC1 ; 
 int /*<<< orphan*/  PORT_TC2 ; 
 int /*<<< orphan*/  PORT_TC3 ; 
 int /*<<< orphan*/  PORT_TC4 ; 
 int /*<<< orphan*/  PORT_TC5 ; 
 int /*<<< orphan*/  PORT_TC6 ; 

__attribute__((used)) static bool gen12_port_hotplug_long_detect(enum hpd_pin pin, u32 val)
{
	switch (pin) {
	case HPD_PORT_D:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC1);
	case HPD_PORT_E:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC2);
	case HPD_PORT_F:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC3);
	case HPD_PORT_G:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC4);
	case HPD_PORT_H:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC5);
	case HPD_PORT_I:
		return val & GEN11_HOTPLUG_CTL_LONG_DETECT(PORT_TC6);
	default:
		return false;
	}
}