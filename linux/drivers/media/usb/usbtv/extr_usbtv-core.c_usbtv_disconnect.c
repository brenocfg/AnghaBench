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
struct usbtv {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/ * udev; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 struct usbtv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbtv_audio_free (struct usbtv*) ; 
 int /*<<< orphan*/  usbtv_video_free (struct usbtv*) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbtv_disconnect(struct usb_interface *intf)
{
	struct usbtv *usbtv = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	if (!usbtv)
		return;

	usbtv_audio_free(usbtv);
	usbtv_video_free(usbtv);

	usb_put_dev(usbtv->udev);
	usbtv->udev = NULL;

	/* the usbtv structure will be deallocated when v4l2 will be
	   done using it */
	v4l2_device_put(&usbtv->v4l2_dev);
}