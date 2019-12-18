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
typedef  enum mtu3_vbus_id_state { ____Placeholder_mtu3_vbus_id_state } mtu3_vbus_id_state ;

/* Variables and functions */
#define  MTU3_ID_FLOAT 131 
#define  MTU3_ID_GROUND 130 
#define  MTU3_VBUS_OFF 129 
#define  MTU3_VBUS_VALID 128 

__attribute__((used)) static char *mailbox_state_string(enum mtu3_vbus_id_state state)
{
	switch (state) {
	case MTU3_ID_FLOAT:
		return "ID_FLOAT";
	case MTU3_ID_GROUND:
		return "ID_GROUND";
	case MTU3_VBUS_OFF:
		return "VBUS_OFF";
	case MTU3_VBUS_VALID:
		return "VBUS_VALID";
	default:
		return "UNKNOWN";
	}
}