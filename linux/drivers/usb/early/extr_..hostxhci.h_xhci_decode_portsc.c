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
 int DEV_PORT_SPEED (int) ; 
 int PORT_CAS ; 
 int PORT_CEC ; 
 int PORT_CONNECT ; 
 int PORT_CSC ; 
 int PORT_OC ; 
 int PORT_OCC ; 
 int PORT_PE ; 
 int PORT_PEC ; 
 int PORT_PLC ; 
 int PORT_POWER ; 
 int PORT_RC ; 
 int PORT_RESET ; 
 int PORT_WKCONN_E ; 
 int PORT_WKDISC_E ; 
 int PORT_WKOC_E ; 
 int PORT_WRC ; 
 int sprintf (char*,char*,...) ; 
 char* xhci_portsc_link_state_string (int) ; 

__attribute__((used)) static inline const char *xhci_decode_portsc(u32 portsc)
{
	static char str[256];
	int ret;

	ret = sprintf(str, "%s %s %s Link:%s PortSpeed:%d ",
		      portsc & PORT_POWER	? "Powered" : "Powered-off",
		      portsc & PORT_CONNECT	? "Connected" : "Not-connected",
		      portsc & PORT_PE		? "Enabled" : "Disabled",
		      xhci_portsc_link_state_string(portsc),
		      DEV_PORT_SPEED(portsc));

	if (portsc & PORT_OC)
		ret += sprintf(str + ret, "OverCurrent ");
	if (portsc & PORT_RESET)
		ret += sprintf(str + ret, "In-Reset ");

	ret += sprintf(str + ret, "Change: ");
	if (portsc & PORT_CSC)
		ret += sprintf(str + ret, "CSC ");
	if (portsc & PORT_PEC)
		ret += sprintf(str + ret, "PEC ");
	if (portsc & PORT_WRC)
		ret += sprintf(str + ret, "WRC ");
	if (portsc & PORT_OCC)
		ret += sprintf(str + ret, "OCC ");
	if (portsc & PORT_RC)
		ret += sprintf(str + ret, "PRC ");
	if (portsc & PORT_PLC)
		ret += sprintf(str + ret, "PLC ");
	if (portsc & PORT_CEC)
		ret += sprintf(str + ret, "CEC ");
	if (portsc & PORT_CAS)
		ret += sprintf(str + ret, "CAS ");

	ret += sprintf(str + ret, "Wake: ");
	if (portsc & PORT_WKCONN_E)
		ret += sprintf(str + ret, "WCE ");
	if (portsc & PORT_WKDISC_E)
		ret += sprintf(str + ret, "WDE ");
	if (portsc & PORT_WKOC_E)
		ret += sprintf(str + ret, "WOE ");

	return str;
}