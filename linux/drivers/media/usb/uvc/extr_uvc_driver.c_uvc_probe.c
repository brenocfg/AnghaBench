#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uvc_device_info {int quirks; } ;
struct TYPE_13__ {char* model; char* serial; int hw_revision; int /*<<< orphan*/  bus_info; int /*<<< orphan*/ * dev; } ;
struct TYPE_12__ {TYPE_6__* mdev; } ;
struct uvc_device {int quirks; char* name; int uvc_version; int /*<<< orphan*/  ref; TYPE_6__ mdev; TYPE_5__ vdev; struct uvc_device_info const* info; int /*<<< orphan*/  intfnum; int /*<<< orphan*/  intf; int /*<<< orphan*/  udev; int /*<<< orphan*/  lock; int /*<<< orphan*/  nmappings; int /*<<< orphan*/  streams; int /*<<< orphan*/  chains; int /*<<< orphan*/  entities; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_3__* cur_altsetting; TYPE_1__* intf_assoc; } ;
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; scalar_t__ driver_info; } ;
struct TYPE_11__ {int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {char* product; char* serial; TYPE_4__ descriptor; int /*<<< orphan*/  devpath; } ;
struct TYPE_9__ {int iInterface; int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_10__ {TYPE_2__ desc; } ;
struct TYPE_8__ {int iFunction; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  UVC_TRACE_PROBE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct uvc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_init (TYPE_6__*) ; 
 scalar_t__ media_device_register (TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct uvc_device*) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uvc_ctrl_init_device (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_delete ; 
 scalar_t__ uvc_parse_control (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*,...) ; 
 struct uvc_device_info const uvc_quirk_none ; 
 int uvc_quirks_param ; 
 scalar_t__ uvc_register_chains (struct uvc_device*) ; 
 scalar_t__ uvc_scan_device (struct uvc_device*) ; 
 int uvc_status_init (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  uvc_unregister_video (struct uvc_device*) ; 
 scalar_t__ v4l2_device_register (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int uvc_probe(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct uvc_device *dev;
	const struct uvc_device_info *info =
		(const struct uvc_device_info *)id->driver_info;
	int function;
	int ret;

	if (id->idVendor && id->idProduct)
		uvc_trace(UVC_TRACE_PROBE, "Probing known UVC device %s "
				"(%04x:%04x)\n", udev->devpath, id->idVendor,
				id->idProduct);
	else
		uvc_trace(UVC_TRACE_PROBE, "Probing generic UVC device %s\n",
				udev->devpath);

	/* Allocate memory for the device and initialize it. */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL)
		return -ENOMEM;

	INIT_LIST_HEAD(&dev->entities);
	INIT_LIST_HEAD(&dev->chains);
	INIT_LIST_HEAD(&dev->streams);
	kref_init(&dev->ref);
	atomic_set(&dev->nmappings, 0);
	mutex_init(&dev->lock);

	dev->udev = usb_get_dev(udev);
	dev->intf = usb_get_intf(intf);
	dev->intfnum = intf->cur_altsetting->desc.bInterfaceNumber;
	dev->info = info ? info : &uvc_quirk_none;
	dev->quirks = uvc_quirks_param == -1
		    ? dev->info->quirks : uvc_quirks_param;

	if (udev->product != NULL)
		strscpy(dev->name, udev->product, sizeof(dev->name));
	else
		snprintf(dev->name, sizeof(dev->name),
			 "UVC Camera (%04x:%04x)",
			 le16_to_cpu(udev->descriptor.idVendor),
			 le16_to_cpu(udev->descriptor.idProduct));

	/*
	 * Add iFunction or iInterface to names when available as additional
	 * distinguishers between interfaces. iFunction is prioritized over
	 * iInterface which matches Windows behavior at the point of writing.
	 */
	if (intf->intf_assoc && intf->intf_assoc->iFunction != 0)
		function = intf->intf_assoc->iFunction;
	else
		function = intf->cur_altsetting->desc.iInterface;
	if (function != 0) {
		size_t len;

		strlcat(dev->name, ": ", sizeof(dev->name));
		len = strlen(dev->name);
		usb_string(udev, function, dev->name + len,
			   sizeof(dev->name) - len);
	}

	/* Parse the Video Class control descriptor. */
	if (uvc_parse_control(dev) < 0) {
		uvc_trace(UVC_TRACE_PROBE, "Unable to parse UVC "
			"descriptors.\n");
		goto error;
	}

	uvc_printk(KERN_INFO, "Found UVC %u.%02x device %s (%04x:%04x)\n",
		dev->uvc_version >> 8, dev->uvc_version & 0xff,
		udev->product ? udev->product : "<unnamed>",
		le16_to_cpu(udev->descriptor.idVendor),
		le16_to_cpu(udev->descriptor.idProduct));

	if (dev->quirks != dev->info->quirks) {
		uvc_printk(KERN_INFO, "Forcing device quirks to 0x%x by module "
			"parameter for testing purpose.\n", dev->quirks);
		uvc_printk(KERN_INFO, "Please report required quirks to the "
			"linux-uvc-devel mailing list.\n");
	}

	/* Initialize the media device and register the V4L2 device. */
#ifdef CONFIG_MEDIA_CONTROLLER
	dev->mdev.dev = &intf->dev;
	strscpy(dev->mdev.model, dev->name, sizeof(dev->mdev.model));
	if (udev->serial)
		strscpy(dev->mdev.serial, udev->serial,
			sizeof(dev->mdev.serial));
	usb_make_path(udev, dev->mdev.bus_info, sizeof(dev->mdev.bus_info));
	dev->mdev.hw_revision = le16_to_cpu(udev->descriptor.bcdDevice);
	media_device_init(&dev->mdev);

	dev->vdev.mdev = &dev->mdev;
#endif
	if (v4l2_device_register(&intf->dev, &dev->vdev) < 0)
		goto error;

	/* Initialize controls. */
	if (uvc_ctrl_init_device(dev) < 0)
		goto error;

	/* Scan the device for video chains. */
	if (uvc_scan_device(dev) < 0)
		goto error;

	/* Register video device nodes. */
	if (uvc_register_chains(dev) < 0)
		goto error;

#ifdef CONFIG_MEDIA_CONTROLLER
	/* Register the media device node */
	if (media_device_register(&dev->mdev) < 0)
		goto error;
#endif
	/* Save our data pointer in the interface data. */
	usb_set_intfdata(intf, dev);

	/* Initialize the interrupt URB. */
	if ((ret = uvc_status_init(dev)) < 0) {
		uvc_printk(KERN_INFO, "Unable to initialize the status "
			"endpoint (%d), status interrupt will not be "
			"supported.\n", ret);
	}

	uvc_trace(UVC_TRACE_PROBE, "UVC device initialized.\n");
	usb_enable_autosuspend(udev);
	return 0;

error:
	uvc_unregister_video(dev);
	kref_put(&dev->ref, uvc_delete);
	return -ENODEV;
}