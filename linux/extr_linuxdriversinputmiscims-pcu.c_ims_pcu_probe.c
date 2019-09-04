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
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int dummy; } ;
struct ims_pcu {int bootloader_mode; int /*<<< orphan*/  data_intf; int /*<<< orphan*/  ctrl_intf; int /*<<< orphan*/  async_firmware_done; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  cmd_mutex; struct usb_device* udev; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMS_PCU_BOOTLOADER_MODE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ims_pcu_attr_group ; 
 int ims_pcu_buffers_alloc (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_buffers_free (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_driver ; 
 int ims_pcu_init_application_mode (struct ims_pcu*) ; 
 int ims_pcu_init_bootloader_mode (struct ims_pcu*) ; 
 int ims_pcu_line_setup (struct ims_pcu*) ; 
 int ims_pcu_parse_cdc_data (struct usb_interface*,struct ims_pcu*) ; 
 int ims_pcu_start_io (struct ims_pcu*) ; 
 int /*<<< orphan*/  ims_pcu_stop_io (struct ims_pcu*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct ims_pcu*) ; 
 struct ims_pcu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usb_driver_claim_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ims_pcu*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,struct ims_pcu*) ; 

__attribute__((used)) static int ims_pcu_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct ims_pcu *pcu;
	int error;

	pcu = kzalloc(sizeof(struct ims_pcu), GFP_KERNEL);
	if (!pcu)
		return -ENOMEM;

	pcu->dev = &intf->dev;
	pcu->udev = udev;
	pcu->bootloader_mode = id->driver_info == IMS_PCU_BOOTLOADER_MODE;
	mutex_init(&pcu->cmd_mutex);
	init_completion(&pcu->cmd_done);
	init_completion(&pcu->async_firmware_done);

	error = ims_pcu_parse_cdc_data(intf, pcu);
	if (error)
		goto err_free_mem;

	error = usb_driver_claim_interface(&ims_pcu_driver,
					   pcu->data_intf, pcu);
	if (error) {
		dev_err(&intf->dev,
			"Unable to claim corresponding data interface: %d\n",
			error);
		goto err_free_mem;
	}

	usb_set_intfdata(pcu->ctrl_intf, pcu);
	usb_set_intfdata(pcu->data_intf, pcu);

	error = ims_pcu_buffers_alloc(pcu);
	if (error)
		goto err_unclaim_intf;

	error = ims_pcu_start_io(pcu);
	if (error)
		goto err_free_buffers;

	error = ims_pcu_line_setup(pcu);
	if (error)
		goto err_stop_io;

	error = sysfs_create_group(&intf->dev.kobj, &ims_pcu_attr_group);
	if (error)
		goto err_stop_io;

	error = pcu->bootloader_mode ?
			ims_pcu_init_bootloader_mode(pcu) :
			ims_pcu_init_application_mode(pcu);
	if (error)
		goto err_remove_sysfs;

	return 0;

err_remove_sysfs:
	sysfs_remove_group(&intf->dev.kobj, &ims_pcu_attr_group);
err_stop_io:
	ims_pcu_stop_io(pcu);
err_free_buffers:
	ims_pcu_buffers_free(pcu);
err_unclaim_intf:
	usb_driver_release_interface(&ims_pcu_driver, pcu->data_intf);
err_free_mem:
	kfree(pcu);
	return error;
}