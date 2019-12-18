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
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
#define  DWC3_LINK_STATE_RECOV 135 
#define  DWC3_LINK_STATE_RESET 134 
#define  DWC3_LINK_STATE_RESUME 133 
#define  DWC3_LINK_STATE_RX_DET 132 
#define  DWC3_LINK_STATE_SS_DIS 131 
#define  DWC3_LINK_STATE_U0 130 
#define  DWC3_LINK_STATE_U2 129 
#define  DWC3_LINK_STATE_U3 128 

__attribute__((used)) static inline const char *
dwc3_gadget_hs_link_string(enum dwc3_link_state link_state)
{
	switch (link_state) {
	case DWC3_LINK_STATE_U0:
		return "On";
	case DWC3_LINK_STATE_U2:
		return "Sleep";
	case DWC3_LINK_STATE_U3:
		return "Suspend";
	case DWC3_LINK_STATE_SS_DIS:
		return "Disconnected";
	case DWC3_LINK_STATE_RX_DET:
		return "Early Suspend";
	case DWC3_LINK_STATE_RECOV:
		return "Recovery";
	case DWC3_LINK_STATE_RESET:
		return "Reset";
	case DWC3_LINK_STATE_RESUME:
		return "Resume";
	default:
		return "UNKNOWN link state\n";
	}
}