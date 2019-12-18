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
struct usb_hcd {int dummy; } ;
struct urb {TYPE_1__* ep; } ;
struct max3421_hcd {struct urb* curr_urb; } ;
struct max3421_ep {int retransmit; } ;
struct TYPE_2__ {struct max3421_ep* hcpriv; } ;

/* Variables and functions */
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 

__attribute__((used)) static void
max3421_slow_retransmit(struct usb_hcd *hcd)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	struct urb *urb = max3421_hcd->curr_urb;
	struct max3421_ep *max3421_ep;

	max3421_ep = urb->ep->hcpriv;
	max3421_ep->retransmit = 1;
	max3421_hcd->curr_urb = NULL;
}