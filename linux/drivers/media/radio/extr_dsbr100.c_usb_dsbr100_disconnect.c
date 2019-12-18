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
struct usb_interface {int dummy; } ;
struct dsbr100_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  videodev; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSB100_ONOFF ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 struct dsbr100_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_dsbr100_disconnect(struct usb_interface *intf)
{
	struct dsbr100_device *radio = usb_get_intfdata(intf);

	mutex_lock(&radio->v4l2_lock);
	/*
	 * Disconnect is also called on unload, and in that case we need to
	 * mute the device. This call will silently fail if it is called
	 * after a physical disconnect.
	 */
	usb_control_msg(radio->usbdev,
		usb_rcvctrlpipe(radio->usbdev, 0),
		DSB100_ONOFF,
		USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
		0x00, 0x00, radio->transfer_buffer, 8, 300);
	usb_set_intfdata(intf, NULL);
	video_unregister_device(&radio->videodev);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->v4l2_lock);
	v4l2_device_put(&radio->v4l2_dev);
}