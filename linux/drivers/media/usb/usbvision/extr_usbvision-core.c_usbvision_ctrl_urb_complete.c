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
struct usb_usbvision {scalar_t__ ctrl_urb_busy; } ;
struct urb {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void usbvision_ctrl_urb_complete(struct urb *urb)
{
	struct usb_usbvision *usbvision = (struct usb_usbvision *)urb->context;

	PDEBUG(DBG_IRQ, "");
	usbvision->ctrl_urb_busy = 0;
}