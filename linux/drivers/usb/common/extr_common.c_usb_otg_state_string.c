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
typedef  enum usb_otg_state { ____Placeholder_usb_otg_state } usb_otg_state ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  OTG_STATE_A_HOST 140 
#define  OTG_STATE_A_IDLE 139 
#define  OTG_STATE_A_PERIPHERAL 138 
#define  OTG_STATE_A_SUSPEND 137 
#define  OTG_STATE_A_VBUS_ERR 136 
#define  OTG_STATE_A_WAIT_BCON 135 
#define  OTG_STATE_A_WAIT_VFALL 134 
#define  OTG_STATE_A_WAIT_VRISE 133 
#define  OTG_STATE_B_HOST 132 
#define  OTG_STATE_B_IDLE 131 
#define  OTG_STATE_B_PERIPHERAL 130 
#define  OTG_STATE_B_SRP_INIT 129 
#define  OTG_STATE_B_WAIT_ACON 128 

const char *usb_otg_state_string(enum usb_otg_state state)
{
	static const char *const names[] = {
		[OTG_STATE_A_IDLE] = "a_idle",
		[OTG_STATE_A_WAIT_VRISE] = "a_wait_vrise",
		[OTG_STATE_A_WAIT_BCON] = "a_wait_bcon",
		[OTG_STATE_A_HOST] = "a_host",
		[OTG_STATE_A_SUSPEND] = "a_suspend",
		[OTG_STATE_A_PERIPHERAL] = "a_peripheral",
		[OTG_STATE_A_WAIT_VFALL] = "a_wait_vfall",
		[OTG_STATE_A_VBUS_ERR] = "a_vbus_err",
		[OTG_STATE_B_IDLE] = "b_idle",
		[OTG_STATE_B_SRP_INIT] = "b_srp_init",
		[OTG_STATE_B_PERIPHERAL] = "b_peripheral",
		[OTG_STATE_B_WAIT_ACON] = "b_wait_acon",
		[OTG_STATE_B_HOST] = "b_host",
	};

	if (state < 0 || state >= ARRAY_SIZE(names))
		return "UNDEFINED";

	return names[state];
}