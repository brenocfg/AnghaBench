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
struct usb_hcd {int /*<<< orphan*/  self; TYPE_1__* driver; } ;
struct urb {int /*<<< orphan*/  reject; TYPE_2__* dev; int /*<<< orphan*/  use_count; int /*<<< orphan*/  urb_list; int /*<<< orphan*/ * hcpriv; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  urbnum; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int (* urb_enqueue ) (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 scalar_t__ is_root_hub (TYPE_2__*) ; 
 scalar_t__ likely (int) ; 
 int map_urb_for_dma (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int rh_urb_enqueue (struct usb_hcd*,struct urb*) ; 
 int stub1 (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usb_get_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb_queue ; 
 int /*<<< orphan*/  usb_put_urb (struct urb*) ; 
 int /*<<< orphan*/  usbmon_urb_submit (int /*<<< orphan*/ *,struct urb*) ; 
 int /*<<< orphan*/  usbmon_urb_submit_error (int /*<<< orphan*/ *,struct urb*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int usb_hcd_submit_urb (struct urb *urb, gfp_t mem_flags)
{
	int			status;
	struct usb_hcd		*hcd = bus_to_hcd(urb->dev->bus);

	/* increment urb's reference count as part of giving it to the HCD
	 * (which will control it).  HCD guarantees that it either returns
	 * an error or calls giveback(), but not both.
	 */
	usb_get_urb(urb);
	atomic_inc(&urb->use_count);
	atomic_inc(&urb->dev->urbnum);
	usbmon_urb_submit(&hcd->self, urb);

	/* NOTE requirements on root-hub callers (usbfs and the hub
	 * driver, for now):  URBs' urb->transfer_buffer must be
	 * valid and usb_buffer_{sync,unmap}() not be needed, since
	 * they could clobber root hub response data.  Also, control
	 * URBs must be submitted in process context with interrupts
	 * enabled.
	 */

	if (is_root_hub(urb->dev)) {
		status = rh_urb_enqueue(hcd, urb);
	} else {
		status = map_urb_for_dma(hcd, urb, mem_flags);
		if (likely(status == 0)) {
			status = hcd->driver->urb_enqueue(hcd, urb, mem_flags);
			if (unlikely(status))
				unmap_urb_for_dma(hcd, urb);
		}
	}

	if (unlikely(status)) {
		usbmon_urb_submit_error(&hcd->self, urb, status);
		urb->hcpriv = NULL;
		INIT_LIST_HEAD(&urb->urb_list);
		atomic_dec(&urb->use_count);
		atomic_dec(&urb->dev->urbnum);
		if (atomic_read(&urb->reject))
			wake_up(&usb_kill_urb_queue);
		usb_put_urb(urb);
	}
	return status;
}