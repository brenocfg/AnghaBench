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
typedef  int u16 ;
struct usb_tt_clear {int tt; int devinfo; int /*<<< orphan*/  clear_list; int /*<<< orphan*/  ep; int /*<<< orphan*/  hcd; } ;
struct usb_tt {int /*<<< orphan*/  lock; int /*<<< orphan*/  clear_work; int /*<<< orphan*/  clear_list; scalar_t__ multi; } ;
struct usb_device {int ttport; int /*<<< orphan*/  bus; scalar_t__ devaddr; int /*<<< orphan*/  dev; struct usb_tt* tt; } ;
struct urb {int pipe; int /*<<< orphan*/  ep; struct usb_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_ENDPOINT_XFER_BULK ; 
 int USB_ENDPOINT_XFER_CONTROL ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct usb_tt_clear* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_pipecontrol (int) ; 
 int usb_pipeendpoint (int) ; 
 scalar_t__ usb_pipein (int) ; 

int usb_hub_clear_tt_buffer(struct urb *urb)
{
	struct usb_device	*udev = urb->dev;
	int			pipe = urb->pipe;
	struct usb_tt		*tt = udev->tt;
	unsigned long		flags;
	struct usb_tt_clear	*clear;

	/* we've got to cope with an arbitrary number of pending TT clears,
	 * since each TT has "at least two" buffers that can need it (and
	 * there can be many TTs per hub).  even if they're uncommon.
	 */
	clear = kmalloc(sizeof *clear, GFP_ATOMIC);
	if (clear == NULL) {
		dev_err(&udev->dev, "can't save CLEAR_TT_BUFFER state\n");
		/* FIXME recover somehow ... RESET_TT? */
		return -ENOMEM;
	}

	/* info that CLEAR_TT_BUFFER needs */
	clear->tt = tt->multi ? udev->ttport : 1;
	clear->devinfo = usb_pipeendpoint (pipe);
	clear->devinfo |= ((u16)udev->devaddr) << 4;
	clear->devinfo |= usb_pipecontrol(pipe)
			? (USB_ENDPOINT_XFER_CONTROL << 11)
			: (USB_ENDPOINT_XFER_BULK << 11);
	if (usb_pipein(pipe))
		clear->devinfo |= 1 << 15;

	/* info for completion callback */
	clear->hcd = bus_to_hcd(udev->bus);
	clear->ep = urb->ep;

	/* tell keventd to clear state for this TT */
	spin_lock_irqsave(&tt->lock, flags);
	list_add_tail(&clear->clear_list, &tt->clear_list);
	schedule_work(&tt->clear_work);
	spin_unlock_irqrestore(&tt->lock, flags);
	return 0;
}