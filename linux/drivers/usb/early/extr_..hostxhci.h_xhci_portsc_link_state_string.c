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

/* Variables and functions */
 int PORT_PLS_MASK ; 
#define  XDEV_COMP_MODE 140 
#define  XDEV_DISABLED 139 
#define  XDEV_HOT_RESET 138 
#define  XDEV_INACTIVE 137 
#define  XDEV_POLLING 136 
#define  XDEV_RECOVERY 135 
#define  XDEV_RESUME 134 
#define  XDEV_RXDETECT 133 
#define  XDEV_TEST_MODE 132 
#define  XDEV_U0 131 
#define  XDEV_U1 130 
#define  XDEV_U2 129 
#define  XDEV_U3 128 

__attribute__((used)) static inline const char *xhci_portsc_link_state_string(u32 portsc)
{
	switch (portsc & PORT_PLS_MASK) {
	case XDEV_U0:
		return "U0";
	case XDEV_U1:
		return "U1";
	case XDEV_U2:
		return "U2";
	case XDEV_U3:
		return "U3";
	case XDEV_DISABLED:
		return "Disabled";
	case XDEV_RXDETECT:
		return "RxDetect";
	case XDEV_INACTIVE:
		return "Inactive";
	case XDEV_POLLING:
		return "Polling";
	case XDEV_RECOVERY:
		return "Recovery";
	case XDEV_HOT_RESET:
		return "Hot Reset";
	case XDEV_COMP_MODE:
		return "Compliance mode";
	case XDEV_TEST_MODE:
		return "Test mode";
	case XDEV_RESUME:
		return "Resume";
	default:
		break;
	}
	return "Unknown";
}