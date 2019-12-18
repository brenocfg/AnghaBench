#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ lpm; } ;
struct ci_hdrc {TYPE_2__ hw_bank; TYPE_1__* platdata; } ;
struct TYPE_3__ {int phy_mode; } ;

/* Variables and functions */
 int DEVLC_PTS (int) ; 
 int DEVLC_PTW ; 
 int DEVLC_STS ; 
 int /*<<< orphan*/  OP_DEVLC ; 
 int /*<<< orphan*/  OP_PORTSC ; 
 int PORTSC_PTS (int) ; 
 int PORTSC_PTW ; 
 int PORTSC_STS ; 
 int PTS_HSIC ; 
 int PTS_SERIAL ; 
 int PTS_ULPI ; 
 int PTS_UTMI ; 
#define  USBPHY_INTERFACE_MODE_HSIC 132 
#define  USBPHY_INTERFACE_MODE_SERIAL 131 
#define  USBPHY_INTERFACE_MODE_ULPI 130 
#define  USBPHY_INTERFACE_MODE_UTMI 129 
#define  USBPHY_INTERFACE_MODE_UTMIW 128 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int,int) ; 

void hw_phymode_configure(struct ci_hdrc *ci)
{
	u32 portsc, lpm, sts = 0;

	switch (ci->platdata->phy_mode) {
	case USBPHY_INTERFACE_MODE_UTMI:
		portsc = PORTSC_PTS(PTS_UTMI);
		lpm = DEVLC_PTS(PTS_UTMI);
		break;
	case USBPHY_INTERFACE_MODE_UTMIW:
		portsc = PORTSC_PTS(PTS_UTMI) | PORTSC_PTW;
		lpm = DEVLC_PTS(PTS_UTMI) | DEVLC_PTW;
		break;
	case USBPHY_INTERFACE_MODE_ULPI:
		portsc = PORTSC_PTS(PTS_ULPI);
		lpm = DEVLC_PTS(PTS_ULPI);
		break;
	case USBPHY_INTERFACE_MODE_SERIAL:
		portsc = PORTSC_PTS(PTS_SERIAL);
		lpm = DEVLC_PTS(PTS_SERIAL);
		sts = 1;
		break;
	case USBPHY_INTERFACE_MODE_HSIC:
		portsc = PORTSC_PTS(PTS_HSIC);
		lpm = DEVLC_PTS(PTS_HSIC);
		break;
	default:
		return;
	}

	if (ci->hw_bank.lpm) {
		hw_write(ci, OP_DEVLC, DEVLC_PTS(7) | DEVLC_PTW, lpm);
		if (sts)
			hw_write(ci, OP_DEVLC, DEVLC_STS, DEVLC_STS);
	} else {
		hw_write(ci, OP_PORTSC, PORTSC_PTS(7) | PORTSC_PTW, portsc);
		if (sts)
			hw_write(ci, OP_PORTSC, PORTSC_STS, PORTSC_STS);
	}
}