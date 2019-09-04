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
#define  HPD_PORT_A 129 
#define  HPD_PORT_B 128 
 int ICP_DDIA_HPD_LONG_DETECT ; 
 int ICP_DDIB_HPD_LONG_DETECT ; 

__attribute__((used)) static bool icp_ddi_port_hotplug_long_detect(enum hpd_pin pin, u32 val)
{
	switch (pin) {
	case HPD_PORT_A:
		return val & ICP_DDIA_HPD_LONG_DETECT;
	case HPD_PORT_B:
		return val & ICP_DDIB_HPD_LONG_DETECT;
	default:
		return false;
	}
}