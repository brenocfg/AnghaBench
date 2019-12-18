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
struct usbtv {int iso_size; int /*<<< orphan*/  udev; int /*<<< orphan*/  v4l2_dev; struct device* dev; } ;
struct device {int dummy; } ;
struct usb_interface {int num_altsetting; TYPE_2__* altsetting; struct device dev; } ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct TYPE_4__ {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usbtv*) ; 
 struct usbtv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (int /*<<< orphan*/ *) ; 
 int usb_endpoint_maxp_mult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usbtv*) ; 
 int usbtv_audio_init (struct usbtv*) ; 
 int /*<<< orphan*/  usbtv_video_free (struct usbtv*) ; 
 int usbtv_video_init (struct usbtv*) ; 
 int /*<<< orphan*/  v4l2_device_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbtv_probe(struct usb_interface *intf,
	const struct usb_device_id *id)
{
	int ret;
	int size;
	struct device *dev = &intf->dev;
	struct usbtv *usbtv;
	struct usb_host_endpoint *ep;

	/* Checks that the device is what we think it is. */
	if (intf->num_altsetting != 2)
		return -ENODEV;
	if (intf->altsetting[1].desc.bNumEndpoints != 4)
		return -ENODEV;

	ep = &intf->altsetting[1].endpoint[0];

	/* Packet size is split into 11 bits of base size and count of
	 * extra multiplies of it.*/
	size = usb_endpoint_maxp(&ep->desc);
	size = size * usb_endpoint_maxp_mult(&ep->desc);

	/* Device structure */
	usbtv = kzalloc(sizeof(struct usbtv), GFP_KERNEL);
	if (usbtv == NULL)
		return -ENOMEM;
	usbtv->dev = dev;
	usbtv->udev = usb_get_dev(interface_to_usbdev(intf));

	usbtv->iso_size = size;

	usb_set_intfdata(intf, usbtv);

	ret = usbtv_video_init(usbtv);
	if (ret < 0)
		goto usbtv_video_fail;

	ret = usbtv_audio_init(usbtv);
	if (ret < 0)
		goto usbtv_audio_fail;

	/* for simplicity we exploit the v4l2_device reference counting */
	v4l2_device_get(&usbtv->v4l2_dev);

	dev_info(dev, "Fushicai USBTV007 Audio-Video Grabber\n");
	return 0;

usbtv_audio_fail:
	/* we must not free at this point */
	usb_get_dev(usbtv->udev);
	usbtv_video_free(usbtv);

usbtv_video_fail:
	usb_set_intfdata(intf, NULL);
	usb_put_dev(usbtv->udev);
	kfree(usbtv);

	return ret;
}