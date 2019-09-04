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
struct kbtab {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct kbtab*) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct kbtab* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kbtab_disconnect(struct usb_interface *intf)
{
	struct kbtab *kbtab = usb_get_intfdata(intf);
	struct usb_device *udev = interface_to_usbdev(intf);

	usb_set_intfdata(intf, NULL);

	input_unregister_device(kbtab->dev);
	usb_free_urb(kbtab->irq);
	usb_free_coherent(udev, 8, kbtab->data, kbtab->data_dma);
	kfree(kbtab);
}