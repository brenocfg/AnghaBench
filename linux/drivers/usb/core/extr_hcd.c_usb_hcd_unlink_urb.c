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
struct usb_hcd {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct urb {struct usb_device* dev; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIDRM ; 
 int EINPROGRESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct urb*,int) ; 
 int /*<<< orphan*/  hcd_urb_unlink_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int unlink1 (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

int usb_hcd_unlink_urb (struct urb *urb, int status)
{
	struct usb_hcd		*hcd;
	struct usb_device	*udev = urb->dev;
	int			retval = -EIDRM;
	unsigned long		flags;

	/* Prevent the device and bus from going away while
	 * the unlink is carried out.  If they are already gone
	 * then urb->use_count must be 0, since disconnected
	 * devices can't have any active URBs.
	 */
	spin_lock_irqsave(&hcd_urb_unlink_lock, flags);
	if (atomic_read(&urb->use_count) > 0) {
		retval = 0;
		usb_get_dev(udev);
	}
	spin_unlock_irqrestore(&hcd_urb_unlink_lock, flags);
	if (retval == 0) {
		hcd = bus_to_hcd(urb->dev->bus);
		retval = unlink1(hcd, urb, status);
		if (retval == 0)
			retval = -EINPROGRESS;
		else if (retval != -EIDRM && retval != -EBUSY)
			dev_dbg(&udev->dev, "hcd_unlink_urb %pK fail %d\n",
					urb, retval);
		usb_put_dev(udev);
	}
	return retval;
}