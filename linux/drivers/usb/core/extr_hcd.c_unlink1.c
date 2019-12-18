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
struct usb_hcd {TYPE_1__* driver; } ;
struct urb {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* urb_dequeue ) (struct usb_hcd*,struct urb*,int) ;} ;

/* Variables and functions */
 scalar_t__ is_root_hub (int /*<<< orphan*/ ) ; 
 int stub1 (struct usb_hcd*,struct urb*,int) ; 
 int usb_rh_urb_dequeue (struct usb_hcd*,struct urb*,int) ; 

__attribute__((used)) static int unlink1(struct usb_hcd *hcd, struct urb *urb, int status)
{
	int		value;

	if (is_root_hub(urb->dev))
		value = usb_rh_urb_dequeue(hcd, urb, status);
	else {

		/* The only reason an HCD might fail this call is if
		 * it has not yet fully queued the urb to begin with.
		 * Such failures should be harmless. */
		value = hcd->driver->urb_dequeue(hcd, urb, status);
	}
	return value;
}