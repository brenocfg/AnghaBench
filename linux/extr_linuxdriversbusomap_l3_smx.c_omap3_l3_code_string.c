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
#define  OMAP_L3_CODE_ADDR_HOLE 134 
#define  OMAP_L3_CODE_IN_BAND_ERR 133 
#define  OMAP_L3_CODE_NOERROR 132 
#define  OMAP_L3_CODE_PROTECT_VIOLATION 131 
#define  OMAP_L3_CODE_REQ_TOUT_NOT_ACCEPT 130 
#define  OMAP_L3_CODE_REQ_TOUT_NO_RESP 129 
#define  OMAP_L3_CODE_UNSUP_CMD 128 

__attribute__((used)) static char *omap3_l3_code_string(u8 code)
{
	switch (code) {
	case OMAP_L3_CODE_NOERROR:
		return "No Error";
	case OMAP_L3_CODE_UNSUP_CMD:
		return "Unsupported Command";
	case OMAP_L3_CODE_ADDR_HOLE:
		return "Address Hole";
	case OMAP_L3_CODE_PROTECT_VIOLATION:
		return "Protection Violation";
	case OMAP_L3_CODE_IN_BAND_ERR:
		return "In-band Error";
	case OMAP_L3_CODE_REQ_TOUT_NOT_ACCEPT:
		return "Request Timeout Not Accepted";
	case OMAP_L3_CODE_REQ_TOUT_NO_RESP:
		return "Request Timeout, no response";
	default:
		return "UNKNOWN error";
	}
}