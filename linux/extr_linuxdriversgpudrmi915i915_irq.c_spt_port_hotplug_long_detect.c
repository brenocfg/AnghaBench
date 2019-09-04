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
#define  HPD_PORT_A 131 
#define  HPD_PORT_B 130 
#define  HPD_PORT_C 129 
#define  HPD_PORT_D 128 
 int PORTA_HOTPLUG_LONG_DETECT ; 
 int PORTB_HOTPLUG_LONG_DETECT ; 
 int PORTC_HOTPLUG_LONG_DETECT ; 
 int PORTD_HOTPLUG_LONG_DETECT ; 

__attribute__((used)) static bool spt_port_hotplug_long_detect(enum hpd_pin pin, u32 val)
{
	switch (pin) {
	case HPD_PORT_A:
		return val & PORTA_HOTPLUG_LONG_DETECT;
	case HPD_PORT_B:
		return val & PORTB_HOTPLUG_LONG_DETECT;
	case HPD_PORT_C:
		return val & PORTC_HOTPLUG_LONG_DETECT;
	case HPD_PORT_D:
		return val & PORTD_HOTPLUG_LONG_DETECT;
	default:
		return false;
	}
}