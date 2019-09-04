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
struct pegasus {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; int /*<<< orphan*/  data_len; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct pegasus*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pegasus_disconnect(struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	input_unregister_device(pegasus->dev);

	usb_free_urb(pegasus->irq);
	usb_free_coherent(interface_to_usbdev(intf),
			  pegasus->data_len, pegasus->data,
			  pegasus->data_dma);

	kfree(pegasus);
	usb_set_intfdata(intf, NULL);
}