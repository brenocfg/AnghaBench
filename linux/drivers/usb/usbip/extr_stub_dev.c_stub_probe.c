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
struct TYPE_3__ {scalar_t__ bDeviceClass; } ;
struct usb_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; int /*<<< orphan*/  devnum; TYPE_2__* bus; TYPE_1__ descriptor; } ;
struct usb_dev_state {int dummy; } ;
struct stub_device {int dummy; } ;
struct bus_id_priv {char status; int /*<<< orphan*/  busid_lock; struct stub_device* sdev; struct usb_device* udev; scalar_t__ shutdown_busid; } ;
struct TYPE_4__ {int /*<<< orphan*/  busnum; int /*<<< orphan*/  bus_name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 char STUB_BUSID_ALLOC ; 
 char STUB_BUSID_OTHER ; 
 char STUB_BUSID_REMOV ; 
 scalar_t__ USB_CLASS_HUB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,...) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct stub_device*) ; 
 struct bus_id_priv* get_busid_priv (char const*) ; 
 int /*<<< orphan*/  put_busid_priv (struct bus_id_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct stub_device* stub_device_alloc (struct usb_device*) ; 
 int /*<<< orphan*/  stub_device_free (struct stub_device*) ; 
 int usb_hub_claim_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_dev_state*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static int stub_probe(struct usb_device *udev)
{
	struct stub_device *sdev = NULL;
	const char *udev_busid = dev_name(&udev->dev);
	struct bus_id_priv *busid_priv;
	int rc = 0;
	char save_status;

	dev_dbg(&udev->dev, "Enter probe\n");

	/* Not sure if this is our device. Allocate here to avoid
	 * calling alloc while holding busid_table lock.
	 */
	sdev = stub_device_alloc(udev);
	if (!sdev)
		return -ENOMEM;

	/* check we should claim or not by busid_table */
	busid_priv = get_busid_priv(udev_busid);
	if (!busid_priv || (busid_priv->status == STUB_BUSID_REMOV) ||
	    (busid_priv->status == STUB_BUSID_OTHER)) {
		dev_info(&udev->dev,
			"%s is not in match_busid table... skip!\n",
			udev_busid);

		/*
		 * Return value should be ENODEV or ENOXIO to continue trying
		 * other matched drivers by the driver core.
		 * See driver_probe_device() in driver/base/dd.c
		 */
		rc = -ENODEV;
		if (!busid_priv)
			goto sdev_free;

		goto call_put_busid_priv;
	}

	if (udev->descriptor.bDeviceClass == USB_CLASS_HUB) {
		dev_dbg(&udev->dev, "%s is a usb hub device... skip!\n",
			 udev_busid);
		rc = -ENODEV;
		goto call_put_busid_priv;
	}

	if (!strcmp(udev->bus->bus_name, "vhci_hcd")) {
		dev_dbg(&udev->dev,
			"%s is attached on vhci_hcd... skip!\n",
			udev_busid);

		rc = -ENODEV;
		goto call_put_busid_priv;
	}


	dev_info(&udev->dev,
		"usbip-host: register new device (bus %u dev %u)\n",
		udev->bus->busnum, udev->devnum);

	busid_priv->shutdown_busid = 0;

	/* set private data to usb_device */
	dev_set_drvdata(&udev->dev, sdev);

	busid_priv->sdev = sdev;
	busid_priv->udev = udev;

	save_status = busid_priv->status;
	busid_priv->status = STUB_BUSID_ALLOC;

	/* release the busid_lock */
	put_busid_priv(busid_priv);

	/*
	 * Claim this hub port.
	 * It doesn't matter what value we pass as owner
	 * (struct dev_state) as long as it is unique.
	 */
	rc = usb_hub_claim_port(udev->parent, udev->portnum,
			(struct usb_dev_state *) udev);
	if (rc) {
		dev_dbg(&udev->dev, "unable to claim port\n");
		goto err_port;
	}

	return 0;

err_port:
	dev_set_drvdata(&udev->dev, NULL);
	usb_put_dev(udev);

	/* we already have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	busid_priv->sdev = NULL;
	busid_priv->status = save_status;
	spin_unlock(&busid_priv->busid_lock);
	/* lock is released - go to free */
	goto sdev_free;

call_put_busid_priv:
	/* release the busid_lock */
	put_busid_priv(busid_priv);

sdev_free:
	stub_device_free(sdev);

	return rc;
}