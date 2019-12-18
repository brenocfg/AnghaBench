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
struct usb_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; } ;
struct usb_dev_state {int dummy; } ;
struct stub_device {int /*<<< orphan*/  udev; } ;
struct bus_id_priv {int shutdown_busid; scalar_t__ status; int /*<<< orphan*/  busid_lock; int /*<<< orphan*/ * sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ STUB_BUSID_ADDED ; 
 scalar_t__ STUB_BUSID_ALLOC ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stub_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bus_id_priv* get_busid_priv (char const*) ; 
 int /*<<< orphan*/  put_busid_priv (struct bus_id_priv*) ; 
 int /*<<< orphan*/  shutdown_busid (struct bus_id_priv*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_device_free (struct stub_device*) ; 
 int usb_hub_release_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_dev_state*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ usbip_in_eh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stub_disconnect(struct usb_device *udev)
{
	struct stub_device *sdev;
	const char *udev_busid = dev_name(&udev->dev);
	struct bus_id_priv *busid_priv;
	int rc;

	dev_dbg(&udev->dev, "Enter disconnect\n");

	busid_priv = get_busid_priv(udev_busid);
	if (!busid_priv) {
		BUG();
		return;
	}

	sdev = dev_get_drvdata(&udev->dev);

	/* get stub_device */
	if (!sdev) {
		dev_err(&udev->dev, "could not get device");
		/* release busid_lock */
		put_busid_priv(busid_priv);
		return;
	}

	dev_set_drvdata(&udev->dev, NULL);

	/* release busid_lock before call to remove device files */
	put_busid_priv(busid_priv);

	/*
	 * NOTE: rx/tx threads are invoked for each usb_device.
	 */

	/* release port */
	rc = usb_hub_release_port(udev->parent, udev->portnum,
				  (struct usb_dev_state *) udev);
	if (rc) {
		dev_dbg(&udev->dev, "unable to release port\n");
		return;
	}

	/* If usb reset is called from event handler */
	if (usbip_in_eh(current))
		return;

	/* we already have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	if (!busid_priv->shutdown_busid)
		busid_priv->shutdown_busid = 1;
	/* release busid_lock */
	spin_unlock(&busid_priv->busid_lock);

	/* shutdown the current connection */
	shutdown_busid(busid_priv);

	usb_put_dev(sdev->udev);

	/* we already have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	/* free sdev */
	busid_priv->sdev = NULL;
	stub_device_free(sdev);

	if (busid_priv->status == STUB_BUSID_ALLOC)
		busid_priv->status = STUB_BUSID_ADDED;
	/* release busid_lock */
	spin_unlock(&busid_priv->busid_lock);
	return;
}