#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
struct acm {int disconnected; int rx_buflimit; int /*<<< orphan*/  port; struct usb_interface* control; struct usb_interface* data; int /*<<< orphan*/  combined_interfaces; int /*<<< orphan*/  notification_buffer; int /*<<< orphan*/  ctrl_dma; int /*<<< orphan*/  ctrl_buffer; int /*<<< orphan*/  ctrlsize; int /*<<< orphan*/  dev; int /*<<< orphan*/ * read_urbs; TYPE_1__* wb; int /*<<< orphan*/  ctrlurb; int /*<<< orphan*/  minor; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wioctl; scalar_t__ country_codes; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ACM_NW ; 
 int /*<<< orphan*/  acm_driver ; 
 int /*<<< orphan*/  acm_kill_urbs (struct acm*) ; 
 int /*<<< orphan*/  acm_read_buffers_free (struct acm*) ; 
 int /*<<< orphan*/  acm_tty_driver ; 
 int /*<<< orphan*/  acm_write_buffers_free (struct acm*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_bmCapabilities ; 
 int /*<<< orphan*/  dev_attr_iCountryCodeRelDate ; 
 int /*<<< orphan*/  dev_attr_wCountryCodes ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct acm* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acm_disconnect(struct usb_interface *intf)
{
	struct acm *acm = usb_get_intfdata(intf);
	struct tty_struct *tty;
	int i;

	/* sibling interface is already cleaning up */
	if (!acm)
		return;

	mutex_lock(&acm->mutex);
	acm->disconnected = true;
	if (acm->country_codes) {
		device_remove_file(&acm->control->dev,
				&dev_attr_wCountryCodes);
		device_remove_file(&acm->control->dev,
				&dev_attr_iCountryCodeRelDate);
	}
	wake_up_all(&acm->wioctl);
	device_remove_file(&acm->control->dev, &dev_attr_bmCapabilities);
	usb_set_intfdata(acm->control, NULL);
	usb_set_intfdata(acm->data, NULL);
	mutex_unlock(&acm->mutex);

	tty = tty_port_tty_get(&acm->port);
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}

	acm_kill_urbs(acm);
	cancel_work_sync(&acm->work);

	tty_unregister_device(acm_tty_driver, acm->minor);

	usb_free_urb(acm->ctrlurb);
	for (i = 0; i < ACM_NW; i++)
		usb_free_urb(acm->wb[i].urb);
	for (i = 0; i < acm->rx_buflimit; i++)
		usb_free_urb(acm->read_urbs[i]);
	acm_write_buffers_free(acm);
	usb_free_coherent(acm->dev, acm->ctrlsize, acm->ctrl_buffer, acm->ctrl_dma);
	acm_read_buffers_free(acm);

	kfree(acm->notification_buffer);

	if (!acm->combined_interfaces)
		usb_driver_release_interface(&acm_driver, intf == acm->control ?
					acm->data : acm->control);

	tty_port_put(&acm->port);
}