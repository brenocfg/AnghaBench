#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int sdp_min; unsigned int sdp_max; unsigned int dcp_min; unsigned int dcp_max; unsigned int cdp_min; unsigned int cdp_max; unsigned int aca_min; unsigned int aca_max; } ;
struct usb_phy {int chg_type; TYPE_1__ chg_cur; } ;

/* Variables and functions */
#define  ACA_TYPE 131 
#define  CDP_TYPE 130 
#define  DCP_TYPE 129 
#define  SDP_TYPE 128 

void usb_phy_get_charger_current(struct usb_phy *usb_phy,
				 unsigned int *min, unsigned int *max)
{
	switch (usb_phy->chg_type) {
	case SDP_TYPE:
		*min = usb_phy->chg_cur.sdp_min;
		*max = usb_phy->chg_cur.sdp_max;
		break;
	case DCP_TYPE:
		*min = usb_phy->chg_cur.dcp_min;
		*max = usb_phy->chg_cur.dcp_max;
		break;
	case CDP_TYPE:
		*min = usb_phy->chg_cur.cdp_min;
		*max = usb_phy->chg_cur.cdp_max;
		break;
	case ACA_TYPE:
		*min = usb_phy->chg_cur.aca_min;
		*max = usb_phy->chg_cur.aca_max;
		break;
	default:
		*min = 0;
		*max = 0;
		break;
	}
}