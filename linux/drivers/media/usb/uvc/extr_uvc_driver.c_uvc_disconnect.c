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
struct uvc_device {int /*<<< orphan*/  ref; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct TYPE_3__ {scalar_t__ bInterfaceSubClass; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ UVC_SC_VIDEOSTREAMING ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct uvc_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_delete ; 
 int /*<<< orphan*/  uvc_unregister_video (struct uvc_device*) ; 

__attribute__((used)) static void uvc_disconnect(struct usb_interface *intf)
{
	struct uvc_device *dev = usb_get_intfdata(intf);

	/* Set the USB interface data to NULL. This can be done outside the
	 * lock, as there's no other reader.
	 */
	usb_set_intfdata(intf, NULL);

	if (intf->cur_altsetting->desc.bInterfaceSubClass ==
	    UVC_SC_VIDEOSTREAMING)
		return;

	uvc_unregister_video(dev);
	kref_put(&dev->ref, uvc_delete);
}