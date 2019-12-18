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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;
struct aiptek {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; int /*<<< orphan*/  urb; int /*<<< orphan*/  inputdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIPTEK_PACKET_LENGTH ; 
 int /*<<< orphan*/  aiptek_attribute_group ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct aiptek*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct aiptek* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aiptek_disconnect(struct usb_interface *intf)
{
	struct aiptek *aiptek = usb_get_intfdata(intf);

	/* Disassociate driver's struct with usb interface
	 */
	usb_set_intfdata(intf, NULL);
	if (aiptek != NULL) {
		/* Free & unhook everything from the system.
		 */
		usb_kill_urb(aiptek->urb);
		input_unregister_device(aiptek->inputdev);
		sysfs_remove_group(&intf->dev.kobj, &aiptek_attribute_group);
		usb_free_urb(aiptek->urb);
		usb_free_coherent(interface_to_usbdev(intf),
				  AIPTEK_PACKET_LENGTH,
				  aiptek->data, aiptek->data_dma);
		kfree(aiptek);
	}
}