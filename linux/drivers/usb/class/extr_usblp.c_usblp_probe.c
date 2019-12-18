#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usblp {int present; size_t current_protocol; int /*<<< orphan*/  intf; struct usblp* device_id_string; struct usblp* statusbuf; struct usblp* readbuf; struct usb_device* dev; TYPE_3__* protocol; int /*<<< orphan*/  ifnum; scalar_t__ bidir; int /*<<< orphan*/  minor; int /*<<< orphan*/  quirks; int /*<<< orphan*/  urbs; int /*<<< orphan*/  wwait; int /*<<< orphan*/  rwait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mut; int /*<<< orphan*/  wmut; } ;
struct usb_interface {int /*<<< orphan*/  dev; int /*<<< orphan*/  minor; TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_4__ descriptor; int /*<<< orphan*/  devnum; } ;
struct TYPE_7__ {int /*<<< orphan*/  alt_setting; } ;
struct TYPE_5__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATUS_BUF_SIZE ; 
 int /*<<< orphan*/  USBLP_BUF_SIZE_IN ; 
 int /*<<< orphan*/  USBLP_DEVICE_ID_SIZE ; 
 int /*<<< orphan*/  USBLP_MINOR_BASE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct usblp*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usblp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usblp*) ; 
 int /*<<< orphan*/  usblp_cache_device_id_string (struct usblp*) ; 
 int /*<<< orphan*/  usblp_check_status (struct usblp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usblp_class ; 
 int /*<<< orphan*/  usblp_quirks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usblp_select_alts (struct usblp*) ; 
 scalar_t__ usblp_set_protocol (struct usblp*,int) ; 

__attribute__((used)) static int usblp_probe(struct usb_interface *intf,
		       const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usblp *usblp;
	int protocol;
	int retval;

	/* Malloc and start initializing usblp structure so we can use it
	 * directly. */
	usblp = kzalloc(sizeof(struct usblp), GFP_KERNEL);
	if (!usblp) {
		retval = -ENOMEM;
		goto abort_ret;
	}
	usblp->dev = dev;
	mutex_init(&usblp->wmut);
	mutex_init(&usblp->mut);
	spin_lock_init(&usblp->lock);
	init_waitqueue_head(&usblp->rwait);
	init_waitqueue_head(&usblp->wwait);
	init_usb_anchor(&usblp->urbs);
	usblp->ifnum = intf->cur_altsetting->desc.bInterfaceNumber;
	usblp->intf = usb_get_intf(intf);

	/* Malloc device ID string buffer to the largest expected length,
	 * since we can re-query it on an ioctl and a dynamic string
	 * could change in length. */
	if (!(usblp->device_id_string = kmalloc(USBLP_DEVICE_ID_SIZE, GFP_KERNEL))) {
		retval = -ENOMEM;
		goto abort;
	}

	/*
	 * Allocate read buffer. We somewhat wastefully
	 * malloc both regardless of bidirectionality, because the
	 * alternate setting can be changed later via an ioctl.
	 */
	if (!(usblp->readbuf = kmalloc(USBLP_BUF_SIZE_IN, GFP_KERNEL))) {
		retval = -ENOMEM;
		goto abort;
	}

	/* Allocate buffer for printer status */
	usblp->statusbuf = kmalloc(STATUS_BUF_SIZE, GFP_KERNEL);
	if (!usblp->statusbuf) {
		retval = -ENOMEM;
		goto abort;
	}

	/* Lookup quirks for this printer. */
	usblp->quirks = usblp_quirks(
		le16_to_cpu(dev->descriptor.idVendor),
		le16_to_cpu(dev->descriptor.idProduct));

	/* Analyze and pick initial alternate settings and endpoints. */
	protocol = usblp_select_alts(usblp);
	if (protocol < 0) {
		dev_dbg(&intf->dev,
			"incompatible printer-class device 0x%4.4X/0x%4.4X\n",
			le16_to_cpu(dev->descriptor.idVendor),
			le16_to_cpu(dev->descriptor.idProduct));
		retval = -ENODEV;
		goto abort;
	}

	/* Setup the selected alternate setting and endpoints. */
	if (usblp_set_protocol(usblp, protocol) < 0) {
		retval = -ENODEV;	/* ->probe isn't ->ioctl */
		goto abort;
	}

	/* Retrieve and store the device ID string. */
	usblp_cache_device_id_string(usblp);

#ifdef DEBUG
	usblp_check_status(usblp, 0);
#endif

	usb_set_intfdata(intf, usblp);

	usblp->present = 1;

	retval = usb_register_dev(intf, &usblp_class);
	if (retval) {
		dev_err(&intf->dev,
			"usblp: Not able to get a minor (base %u, slice default): %d\n",
			USBLP_MINOR_BASE, retval);
		goto abort_intfdata;
	}
	usblp->minor = intf->minor;
	dev_info(&intf->dev,
		"usblp%d: USB %sdirectional printer dev %d if %d alt %d proto %d vid 0x%4.4X pid 0x%4.4X\n",
		usblp->minor, usblp->bidir ? "Bi" : "Uni", dev->devnum,
		usblp->ifnum,
		usblp->protocol[usblp->current_protocol].alt_setting,
		usblp->current_protocol,
		le16_to_cpu(usblp->dev->descriptor.idVendor),
		le16_to_cpu(usblp->dev->descriptor.idProduct));

	return 0;

abort_intfdata:
	usb_set_intfdata(intf, NULL);
abort:
	kfree(usblp->readbuf);
	kfree(usblp->statusbuf);
	kfree(usblp->device_id_string);
	usb_put_intf(usblp->intf);
	kfree(usblp);
abort_ret:
	return retval;
}