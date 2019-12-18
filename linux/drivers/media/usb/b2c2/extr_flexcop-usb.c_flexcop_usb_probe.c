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
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct flexcop_usb {struct usb_interface* uintf; struct usb_device* udev; int /*<<< orphan*/  data_mutex; struct flexcop_device* fc_dev; } ;
struct flexcop_device {int pid_filtering; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  bus_type; int /*<<< orphan*/  stream_control; int /*<<< orphan*/  get_mac_addr; int /*<<< orphan*/  i2c_request; int /*<<< orphan*/  write_ibi_reg; int /*<<< orphan*/  read_ibi_reg; struct flexcop_usb* bus_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FC_USB ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  flexcop_device_exit (struct flexcop_device*) ; 
 int flexcop_device_initialize (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_device_kfree (struct flexcop_device*) ; 
 struct flexcop_device* flexcop_device_kmalloc (int) ; 
 int /*<<< orphan*/  flexcop_usb_exit (struct flexcop_usb*) ; 
 int /*<<< orphan*/  flexcop_usb_get_mac_addr ; 
 int /*<<< orphan*/  flexcop_usb_i2c_request ; 
 int flexcop_usb_init (struct flexcop_usb*) ; 
 int /*<<< orphan*/  flexcop_usb_read_ibi_reg ; 
 int /*<<< orphan*/  flexcop_usb_stream_control ; 
 int flexcop_usb_transfer_init (struct flexcop_usb*) ; 
 int /*<<< orphan*/  flexcop_usb_write_ibi_reg ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flexcop_usb_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct flexcop_usb *fc_usb = NULL;
	struct flexcop_device *fc = NULL;
	int ret;

	if ((fc = flexcop_device_kmalloc(sizeof(struct flexcop_usb))) == NULL) {
		err("out of memory\n");
		return -ENOMEM;
	}

	/* general flexcop init */
	fc_usb = fc->bus_specific;
	fc_usb->fc_dev = fc;
	mutex_init(&fc_usb->data_mutex);

	fc->read_ibi_reg  = flexcop_usb_read_ibi_reg;
	fc->write_ibi_reg = flexcop_usb_write_ibi_reg;
	fc->i2c_request = flexcop_usb_i2c_request;
	fc->get_mac_addr = flexcop_usb_get_mac_addr;

	fc->stream_control = flexcop_usb_stream_control;

	fc->pid_filtering = 1;
	fc->bus_type = FC_USB;

	fc->dev = &udev->dev;
	fc->owner = THIS_MODULE;

	/* bus specific part */
	fc_usb->udev = udev;
	fc_usb->uintf = intf;
	if ((ret = flexcop_usb_init(fc_usb)) != 0)
		goto err_kfree;

	/* init flexcop */
	if ((ret = flexcop_device_initialize(fc)) != 0)
		goto err_usb_exit;

	/* xfer init */
	if ((ret = flexcop_usb_transfer_init(fc_usb)) != 0)
		goto err_fc_exit;

	info("%s successfully initialized and connected.", DRIVER_NAME);
	return 0;

err_fc_exit:
	flexcop_device_exit(fc);
err_usb_exit:
	flexcop_usb_exit(fc_usb);
err_kfree:
	flexcop_device_kfree(fc);
	return ret;
}