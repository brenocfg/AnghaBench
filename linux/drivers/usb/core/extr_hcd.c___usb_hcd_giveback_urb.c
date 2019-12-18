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
struct usb_hcd {int /*<<< orphan*/  self; } ;
struct usb_anchor {int dummy; } ;
struct urb {int unlinked; int transfer_flags; scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int status; int /*<<< orphan*/  reject; int /*<<< orphan*/  use_count; int /*<<< orphan*/  (* complete ) (struct urb*) ;int /*<<< orphan*/ * hcpriv; struct usb_anchor* anchor; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int URB_SHORT_NOT_OK ; 
 int /*<<< orphan*/  USB_LED_EVENT_HOST ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct urb*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usb_anchor_resume_wakeups (struct usb_anchor*) ; 
 int /*<<< orphan*/  usb_anchor_suspend_wakeups (struct usb_anchor*) ; 
 int /*<<< orphan*/  usb_kill_urb_queue ; 
 int /*<<< orphan*/  usb_led_activity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 
 int /*<<< orphan*/  usbmon_urb_complete (int /*<<< orphan*/ *,struct urb*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __usb_hcd_giveback_urb(struct urb *urb)
{
	struct usb_hcd *hcd = bus_to_hcd(urb->dev->bus);
	struct usb_anchor *anchor = urb->anchor;
	int status = urb->unlinked;

	urb->hcpriv = NULL;
	if (unlikely((urb->transfer_flags & URB_SHORT_NOT_OK) &&
	    urb->actual_length < urb->transfer_buffer_length &&
	    !status))
		status = -EREMOTEIO;

	unmap_urb_for_dma(hcd, urb);
	usbmon_urb_complete(&hcd->self, urb, status);
	usb_anchor_suspend_wakeups(anchor);
	usb_unanchor_urb(urb);
	if (likely(status == 0))
		usb_led_activity(USB_LED_EVENT_HOST);

	/* pass ownership to the completion handler */
	urb->status = status;
	urb->complete(urb);

	usb_anchor_resume_wakeups(anchor);
	atomic_dec(&urb->use_count);
	if (unlikely(atomic_read(&urb->reject)))
		wake_up(&usb_kill_urb_queue);
	usb_put_urb(urb);
}