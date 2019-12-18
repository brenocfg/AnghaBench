#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; TYPE_2__* altsetting; } ;
struct usb_device_id {int dummy; } ;
struct gs_usb {int byte_order; int icount; TYPE_3__** canch; int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  udev; int /*<<< orphan*/  active_channels; } ;
struct gs_host_config {int byte_order; int icount; TYPE_3__** canch; int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  udev; int /*<<< orphan*/  active_channels; } ;
struct gs_device_config {int byte_order; int icount; TYPE_3__** canch; int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/  udev; int /*<<< orphan*/  active_channels; } ;
struct TYPE_9__ {struct gs_usb* parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_8__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int GS_MAX_INTF ; 
 int /*<<< orphan*/  GS_USB_BREQ_DEVICE_CONFIG ; 
 int /*<<< orphan*/  GS_USB_BREQ_HOST_FORMAT ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  gs_destroy_candev (TYPE_3__*) ; 
 TYPE_3__* gs_make_candev (unsigned int,struct usb_interface*,struct gs_usb*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gs_usb*) ; 
 struct gs_usb* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct gs_usb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct gs_usb*,int,int) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct gs_usb*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_usb_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct gs_usb *dev;
	int rc = -ENOMEM;
	unsigned int icount, i;
	struct gs_host_config *hconf;
	struct gs_device_config *dconf;

	hconf = kmalloc(sizeof(*hconf), GFP_KERNEL);
	if (!hconf)
		return -ENOMEM;

	hconf->byte_order = 0x0000beef;

	/* send host config */
	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_sndctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_HOST_FORMAT,
			     USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     1,
			     intf->altsetting[0].desc.bInterfaceNumber,
			     hconf,
			     sizeof(*hconf),
			     1000);

	kfree(hconf);

	if (rc < 0) {
		dev_err(&intf->dev, "Couldn't send data format (err=%d)\n",
			rc);
		return rc;
	}

	dconf = kmalloc(sizeof(*dconf), GFP_KERNEL);
	if (!dconf)
		return -ENOMEM;

	/* read device config */
	rc = usb_control_msg(interface_to_usbdev(intf),
			     usb_rcvctrlpipe(interface_to_usbdev(intf), 0),
			     GS_USB_BREQ_DEVICE_CONFIG,
			     USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			     1,
			     intf->altsetting[0].desc.bInterfaceNumber,
			     dconf,
			     sizeof(*dconf),
			     1000);
	if (rc < 0) {
		dev_err(&intf->dev, "Couldn't get device config: (err=%d)\n",
			rc);
		kfree(dconf);
		return rc;
	}

	icount = dconf->icount + 1;
	dev_info(&intf->dev, "Configuring for %d interfaces\n", icount);

	if (icount > GS_MAX_INTF) {
		dev_err(&intf->dev,
			"Driver cannot handle more that %d CAN interfaces\n",
			GS_MAX_INTF);
		kfree(dconf);
		return -EINVAL;
	}

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		kfree(dconf);
		return -ENOMEM;
	}

	init_usb_anchor(&dev->rx_submitted);

	atomic_set(&dev->active_channels, 0);

	usb_set_intfdata(intf, dev);
	dev->udev = interface_to_usbdev(intf);

	for (i = 0; i < icount; i++) {
		dev->canch[i] = gs_make_candev(i, intf, dconf);
		if (IS_ERR_OR_NULL(dev->canch[i])) {
			/* save error code to return later */
			rc = PTR_ERR(dev->canch[i]);

			/* on failure destroy previously created candevs */
			icount = i;
			for (i = 0; i < icount; i++)
				gs_destroy_candev(dev->canch[i]);

			usb_kill_anchored_urbs(&dev->rx_submitted);
			kfree(dconf);
			kfree(dev);
			return rc;
		}
		dev->canch[i]->parent = dev;
	}

	kfree(dconf);

	return 0;
}