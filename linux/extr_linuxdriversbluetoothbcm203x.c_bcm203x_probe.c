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
struct usb_interface {int /*<<< orphan*/  dev; TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {struct usb_device_id const* size; struct usb_interface* data; } ;
struct bcm203x_data {int /*<<< orphan*/  work; scalar_t__ fw_sent; struct usb_device_id const* fw_size; int /*<<< orphan*/  buffer; int /*<<< orphan*/  urb; int /*<<< orphan*/  fw_data; int /*<<< orphan*/  state; struct usb_device* udev; } ;
struct TYPE_3__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM203X_LOAD_MINIDRV ; 
 int /*<<< orphan*/  BCM203X_OUT_EP ; 
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm203x_complete ; 
 int /*<<< orphan*/  bcm203x_work ; 
 struct bcm203x_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (struct usb_interface*,struct usb_device_id const*,int /*<<< orphan*/ ) ; 
 int max_t (int /*<<< orphan*/ ,struct usb_device_id const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct usb_interface*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_id const*,int /*<<< orphan*/ ,struct bcm203x_data*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct bcm203x_data*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm203x_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	const struct firmware *firmware;
	struct usb_device *udev = interface_to_usbdev(intf);
	struct bcm203x_data *data;
	int size;

	BT_DBG("intf %p id %p", intf, id);

	if (intf->cur_altsetting->desc.bInterfaceNumber != 0)
		return -ENODEV;

	data = devm_kzalloc(&intf->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->udev  = udev;
	data->state = BCM203X_LOAD_MINIDRV;

	data->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!data->urb)
		return -ENOMEM;

	if (request_firmware(&firmware, "BCM2033-MD.hex", &udev->dev) < 0) {
		BT_ERR("Mini driver request failed");
		usb_free_urb(data->urb);
		return -EIO;
	}

	BT_DBG("minidrv data %p size %zu", firmware->data, firmware->size);

	size = max_t(uint, firmware->size, 4096);

	data->buffer = kmalloc(size, GFP_KERNEL);
	if (!data->buffer) {
		BT_ERR("Can't allocate memory for mini driver");
		release_firmware(firmware);
		usb_free_urb(data->urb);
		return -ENOMEM;
	}

	memcpy(data->buffer, firmware->data, firmware->size);

	usb_fill_bulk_urb(data->urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
			data->buffer, firmware->size, bcm203x_complete, data);

	release_firmware(firmware);

	if (request_firmware(&firmware, "BCM2033-FW.bin", &udev->dev) < 0) {
		BT_ERR("Firmware request failed");
		usb_free_urb(data->urb);
		kfree(data->buffer);
		return -EIO;
	}

	BT_DBG("firmware data %p size %zu", firmware->data, firmware->size);

	data->fw_data = kmemdup(firmware->data, firmware->size, GFP_KERNEL);
	if (!data->fw_data) {
		BT_ERR("Can't allocate memory for firmware image");
		release_firmware(firmware);
		usb_free_urb(data->urb);
		kfree(data->buffer);
		return -ENOMEM;
	}

	data->fw_size = firmware->size;
	data->fw_sent = 0;

	release_firmware(firmware);

	INIT_WORK(&data->work, bcm203x_work);

	usb_set_intfdata(intf, data);

	/* use workqueue to have a small delay */
	schedule_work(&data->work);

	return 0;
}