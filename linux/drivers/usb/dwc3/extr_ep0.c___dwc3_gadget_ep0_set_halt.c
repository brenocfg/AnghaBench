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
struct usb_ep {int dummy; } ;
struct dwc3_ep {struct dwc3* dwc; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc3_ep0_stall_and_restart (struct dwc3*) ; 
 struct dwc3_ep* to_dwc3_ep (struct usb_ep*) ; 

int __dwc3_gadget_ep0_set_halt(struct usb_ep *ep, int value)
{
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;

	dwc3_ep0_stall_and_restart(dwc);

	return 0;
}