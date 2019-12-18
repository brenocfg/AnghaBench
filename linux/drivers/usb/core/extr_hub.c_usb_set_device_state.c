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
struct usb_device {scalar_t__ state; int quirks; int /*<<< orphan*/  dev; int /*<<< orphan*/  active_duration; TYPE_2__* actconfig; scalar_t__ parent; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;
struct TYPE_3__ {int bmAttributes; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int USB_CONFIG_ATT_WAKEUP ; 
 int USB_QUIRK_IGNORE_REMOTE_WAKEUP ; 
 int USB_STATE_CONFIGURED ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_state_lock ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  recursively_mark_NOTATTACHED (struct usb_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void usb_set_device_state(struct usb_device *udev,
		enum usb_device_state new_state)
{
	unsigned long flags;
	int wakeup = -1;

	spin_lock_irqsave(&device_state_lock, flags);
	if (udev->state == USB_STATE_NOTATTACHED)
		;	/* do nothing */
	else if (new_state != USB_STATE_NOTATTACHED) {

		/* root hub wakeup capabilities are managed out-of-band
		 * and may involve silicon errata ... ignore them here.
		 */
		if (udev->parent) {
			if (udev->state == USB_STATE_SUSPENDED
					|| new_state == USB_STATE_SUSPENDED)
				;	/* No change to wakeup settings */
			else if (new_state == USB_STATE_CONFIGURED)
				wakeup = (udev->quirks &
					USB_QUIRK_IGNORE_REMOTE_WAKEUP) ? 0 :
					udev->actconfig->desc.bmAttributes &
					USB_CONFIG_ATT_WAKEUP;
			else
				wakeup = 0;
		}
		if (udev->state == USB_STATE_SUSPENDED &&
			new_state != USB_STATE_SUSPENDED)
			udev->active_duration -= jiffies;
		else if (new_state == USB_STATE_SUSPENDED &&
				udev->state != USB_STATE_SUSPENDED)
			udev->active_duration += jiffies;
		udev->state = new_state;
	} else
		recursively_mark_NOTATTACHED(udev);
	spin_unlock_irqrestore(&device_state_lock, flags);
	if (wakeup >= 0)
		device_set_wakeup_capable(&udev->dev, wakeup);
}