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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_2__ dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {scalar_t__ bInterfaceClass; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct ims_pcu {scalar_t__ bootloader_mode; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_COMM ; 
 int /*<<< orphan*/  ims_pcu_attr_group ; 
 int /*<<< orphan*/  ims_pcu_buffers_free (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_destroy_application_mode (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_destroy_bootloader_mode (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_stop_io (struct ims_pcu*) ; 
 int /*<<< orphan*/  kfree (struct ims_pcu*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ims_pcu* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ims_pcu_disconnect(struct usb_interface *intf)
{
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	struct usb_host_interface *alt = intf->cur_altsetting;

	usb_set_intfdata(intf, NULL);

	/*
	 * See if we are dealing with control or data interface. The cleanup
	 * happens when we unbind primary (control) interface.
	 */
	if (alt->desc.bInterfaceClass != USB_CLASS_COMM)
		return;

	sysfs_remove_group(&intf->dev.kobj, &ims_pcu_attr_group);

	ims_pcu_stop_io(pcu);

	if (pcu->bootloader_mode)
		ims_pcu_destroy_bootloader_mode(pcu);
	else
		ims_pcu_destroy_application_mode(pcu);

	ims_pcu_buffers_free(pcu);
	kfree(pcu);
}