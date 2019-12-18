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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static char *intel_dsm_port_name(u8 id)
{
	switch (id) {
	case 0:
		return "Reserved";
	case 1:
		return "Analog VGA";
	case 2:
		return "LVDS";
	case 3:
		return "Reserved";
	case 4:
		return "HDMI/DVI_B";
	case 5:
		return "HDMI/DVI_C";
	case 6:
		return "HDMI/DVI_D";
	case 7:
		return "DisplayPort_A";
	case 8:
		return "DisplayPort_B";
	case 9:
		return "DisplayPort_C";
	case 0xa:
		return "DisplayPort_D";
	case 0xb:
	case 0xc:
	case 0xd:
		return "Reserved";
	case 0xe:
		return "WiDi";
	default:
		return "bad type";
	}
}