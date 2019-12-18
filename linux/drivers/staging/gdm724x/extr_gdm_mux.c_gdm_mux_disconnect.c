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
struct usb_device {int dummy; } ;
struct tty_dev {struct tty_dev* priv_dev; } ;
struct mux_dev {struct mux_dev* priv_dev; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct tty_dev*) ; 
 int /*<<< orphan*/  release_usb (struct tty_dev*) ; 
 int /*<<< orphan*/  unregister_lte_tty_device (struct tty_dev*) ; 
 struct tty_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void gdm_mux_disconnect(struct usb_interface *intf)
{
	struct tty_dev *tty_dev;
	struct mux_dev *mux_dev;
	struct usb_device *usbdev = interface_to_usbdev(intf);

	tty_dev = usb_get_intfdata(intf);

	mux_dev = tty_dev->priv_dev;

	release_usb(mux_dev);
	unregister_lte_tty_device(tty_dev);

	kfree(mux_dev);
	kfree(tty_dev);

	usb_put_dev(usbdev);
}