#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; scalar_t__ serial; scalar_t__ product; } ;
struct TYPE_5__ {int quality; int /*<<< orphan*/  read; int /*<<< orphan*/ * name; } ;
struct chaoskey {int in_ep; int reads_started; int size; int present; int hwrng_registered; TYPE_2__ hwrng; int /*<<< orphan*/ * name; int /*<<< orphan*/  rng_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_q; int /*<<< orphan*/ * buf; int /*<<< orphan*/  urb; int /*<<< orphan*/  interface; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ ALEA_VENDOR_ID ; 
 int CHAOSKEY_BUF_LEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  chaos_read_callback ; 
 int /*<<< orphan*/  chaoskey_class ; 
 TYPE_3__ chaoskey_driver ; 
 int /*<<< orphan*/  chaoskey_free (struct chaoskey*) ; 
 int /*<<< orphan*/  chaoskey_rng_read ; 
 scalar_t__ hwrng_register (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct chaoskey* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dbg (struct usb_interface*,char*,...) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_err (struct usb_interface*,char*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct chaoskey*) ; 
 int usb_find_bulk_in_endpoint (struct usb_host_interface*,struct usb_endpoint_descriptor**) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct chaoskey*) ; 

__attribute__((used)) static int chaoskey_probe(struct usb_interface *interface,
			  const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_host_interface *altsetting = interface->cur_altsetting;
	struct usb_endpoint_descriptor *epd;
	int in_ep;
	struct chaoskey *dev;
	int result = -ENOMEM;
	int size;
	int res;

	usb_dbg(interface, "probe %s-%s", udev->product, udev->serial);

	/* Find the first bulk IN endpoint and its packet size */
	res = usb_find_bulk_in_endpoint(altsetting, &epd);
	if (res) {
		usb_dbg(interface, "no IN endpoint found");
		return res;
	}

	in_ep = usb_endpoint_num(epd);
	size = usb_endpoint_maxp(epd);

	/* Validate endpoint and size */
	if (size <= 0) {
		usb_dbg(interface, "invalid size (%d)", size);
		return -ENODEV;
	}

	if (size > CHAOSKEY_BUF_LEN) {
		usb_dbg(interface, "size reduced from %d to %d\n",
			size, CHAOSKEY_BUF_LEN);
		size = CHAOSKEY_BUF_LEN;
	}

	/* Looks good, allocate and initialize */

	dev = kzalloc(sizeof(struct chaoskey), GFP_KERNEL);

	if (dev == NULL)
		goto out;

	dev->interface = usb_get_intf(interface);

	dev->buf = kmalloc(size, GFP_KERNEL);

	if (dev->buf == NULL)
		goto out;

	dev->urb = usb_alloc_urb(0, GFP_KERNEL);

	if (!dev->urb)
		goto out;

	usb_fill_bulk_urb(dev->urb,
		udev,
		usb_rcvbulkpipe(udev, in_ep),
		dev->buf,
		size,
		chaos_read_callback,
		dev);

	/* Construct a name using the product and serial values. Each
	 * device needs a unique name for the hwrng code
	 */

	if (udev->product && udev->serial) {
		dev->name = kasprintf(GFP_KERNEL, "%s-%s", udev->product,
				      udev->serial);
		if (dev->name == NULL)
			goto out;
	}

	dev->in_ep = in_ep;

	if (le16_to_cpu(udev->descriptor.idVendor) != ALEA_VENDOR_ID)
		dev->reads_started = true;

	dev->size = size;
	dev->present = true;

	init_waitqueue_head(&dev->wait_q);

	mutex_init(&dev->lock);
	mutex_init(&dev->rng_lock);

	usb_set_intfdata(interface, dev);

	result = usb_register_dev(interface, &chaoskey_class);
	if (result) {
		usb_err(interface, "Unable to allocate minor number.");
		goto out;
	}

	dev->hwrng.name = dev->name ? dev->name : chaoskey_driver.name;
	dev->hwrng.read = chaoskey_rng_read;
	dev->hwrng.quality = 1024;

	dev->hwrng_registered = (hwrng_register(&dev->hwrng) == 0);
	if (!dev->hwrng_registered)
		usb_err(interface, "Unable to register with hwrng");

	usb_enable_autosuspend(udev);

	usb_dbg(interface, "chaoskey probe success, size %d", dev->size);
	return 0;

out:
	usb_set_intfdata(interface, NULL);
	chaoskey_free(dev);
	return result;
}