#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_otg {int state; TYPE_1__* host; } ;
struct TYPE_5__ {int is_a_peripheral; } ;
struct musb {int port1_status; TYPE_3__* xceiv; scalar_t__ is_active; TYPE_2__ g; int /*<<< orphan*/  hcd; } ;
struct TYPE_6__ {struct usb_otg* otg; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_hnp_enable; } ;

/* Variables and functions */
#define  OTG_STATE_A_HOST 130 
 int OTG_STATE_A_PERIPHERAL ; 
#define  OTG_STATE_A_SUSPEND 129 
 int OTG_STATE_A_WAIT_BCON ; 
#define  OTG_STATE_A_WAIT_VFALL 128 
 int OTG_STATE_B_IDLE ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_POWER ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

void musb_root_disconnect(struct musb *musb)
{
	struct usb_otg	*otg = musb->xceiv->otg;

	musb->port1_status = USB_PORT_STAT_POWER
			| (USB_PORT_STAT_C_CONNECTION << 16);

	usb_hcd_poll_rh_status(musb->hcd);
	musb->is_active = 0;

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_SUSPEND:
		if (otg->host->b_hnp_enable) {
			musb->xceiv->otg->state = OTG_STATE_A_PERIPHERAL;
			musb->g.is_a_peripheral = 1;
			break;
		}
		/* FALLTHROUGH */
	case OTG_STATE_A_HOST:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
		musb->is_active = 0;
		break;
	case OTG_STATE_A_WAIT_VFALL:
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		break;
	default:
		musb_dbg(musb, "host disconnect (%s)",
			usb_otg_state_string(musb->xceiv->otg->state));
	}
}