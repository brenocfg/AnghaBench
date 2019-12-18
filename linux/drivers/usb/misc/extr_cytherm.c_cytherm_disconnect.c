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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_cytherm {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_cytherm*) ; 
 struct usb_cytherm* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cytherm_disconnect(struct usb_interface *interface)
{
	struct usb_cytherm *dev;

	dev = usb_get_intfdata (interface);

	/* first remove the files, then NULL the pointer */
	usb_set_intfdata (interface, NULL);

	usb_put_dev(dev->udev);

	kfree(dev);

	dev_info(&interface->dev, "Cypress thermometer now disconnected\n");
}