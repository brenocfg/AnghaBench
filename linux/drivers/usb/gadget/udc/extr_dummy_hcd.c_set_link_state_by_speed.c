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
struct dummy_hcd {int port_status; int old_status; scalar_t__ rh_state; int active; struct dummy* dum; } ;
struct dummy {scalar_t__ udc_suspended; int /*<<< orphan*/  pullup; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ DUMMY_RH_SUSPENDED ; 
 scalar_t__ HCD_USB3 ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LINK_STATE ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_POWER ; 
 int USB_PORT_STAT_SPEED_5GBPS ; 
 int USB_PORT_STAT_SUSPEND ; 
 int USB_SS_PORT_LS_U0 ; 
 int USB_SS_PORT_STAT_POWER ; 
 TYPE_1__* dummy_hcd_to_hcd (struct dummy_hcd*) ; 

__attribute__((used)) static void set_link_state_by_speed(struct dummy_hcd *dum_hcd)
{
	struct dummy *dum = dum_hcd->dum;

	if (dummy_hcd_to_hcd(dum_hcd)->speed == HCD_USB3) {
		if ((dum_hcd->port_status & USB_SS_PORT_STAT_POWER) == 0) {
			dum_hcd->port_status = 0;
		} else if (!dum->pullup || dum->udc_suspended) {
			/* UDC suspend must cause a disconnect */
			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE);
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		} else {
			/* device is connected and not suspended */
			dum_hcd->port_status |= (USB_PORT_STAT_CONNECTION |
						 USB_PORT_STAT_SPEED_5GBPS) ;
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			if ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) &&
			    (dum_hcd->port_status &
			     USB_PORT_STAT_LINK_STATE) == USB_SS_PORT_LS_U0 &&
			    dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		}
	} else {
		if ((dum_hcd->port_status & USB_PORT_STAT_POWER) == 0) {
			dum_hcd->port_status = 0;
		} else if (!dum->pullup || dum->udc_suspended) {
			/* UDC suspend must cause a disconnect */
			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE |
						USB_PORT_STAT_LOW_SPEED |
						USB_PORT_STAT_HIGH_SPEED |
						USB_PORT_STAT_SUSPEND);
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		} else {
			dum_hcd->port_status |= USB_PORT_STAT_CONNECTION;
			if ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			if ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) == 0)
				dum_hcd->port_status &= ~USB_PORT_STAT_SUSPEND;
			else if ((dum_hcd->port_status &
				  USB_PORT_STAT_SUSPEND) == 0 &&
					dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		}
	}
}