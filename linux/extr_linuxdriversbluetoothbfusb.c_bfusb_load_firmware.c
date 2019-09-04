#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfusb_data {TYPE_1__* udev; int /*<<< orphan*/  bulk_out_ep; } ;
struct TYPE_6__ {scalar_t__* toggle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFUSB_BLOCK_TIMEOUT ; 
 scalar_t__ BFUSB_MAX_BLOCK_SIZE ; 
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*,TYPE_1__*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_REQ_SET_CONFIGURATION ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int min_t (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  uint ; 
 int usb_bulk_msg (TYPE_1__*,int,unsigned char*,int,int*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_sndbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfusb_load_firmware(struct bfusb_data *data,
			       const unsigned char *firmware, int count)
{
	unsigned char *buf;
	int err, pipe, len, size, sent = 0;

	BT_DBG("bfusb %p udev %p", data, data->udev);

	BT_INFO("BlueFRITZ! USB loading firmware");

	buf = kmalloc(BFUSB_MAX_BLOCK_SIZE + 3, GFP_KERNEL);
	if (!buf) {
		BT_ERR("Can't allocate memory chunk for firmware");
		return -ENOMEM;
	}

	pipe = usb_sndctrlpipe(data->udev, 0);

	if (usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 1, 0, NULL, 0, USB_CTRL_SET_TIMEOUT) < 0) {
		BT_ERR("Can't change to loading configuration");
		kfree(buf);
		return -EBUSY;
	}

	data->udev->toggle[0] = data->udev->toggle[1] = 0;

	pipe = usb_sndbulkpipe(data->udev, data->bulk_out_ep);

	while (count) {
		size = min_t(uint, count, BFUSB_MAX_BLOCK_SIZE + 3);

		memcpy(buf, firmware + sent, size);

		err = usb_bulk_msg(data->udev, pipe, buf, size,
					&len, BFUSB_BLOCK_TIMEOUT);

		if (err || (len != size)) {
			BT_ERR("Error in firmware loading");
			goto error;
		}

		sent  += size;
		count -= size;
	}

	err = usb_bulk_msg(data->udev, pipe, NULL, 0,
					&len, BFUSB_BLOCK_TIMEOUT);
	if (err < 0) {
		BT_ERR("Error in null packet request");
		goto error;
	}

	pipe = usb_sndctrlpipe(data->udev, 0);

	err = usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 2, 0, NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (err < 0) {
		BT_ERR("Can't change to running configuration");
		goto error;
	}

	data->udev->toggle[0] = data->udev->toggle[1] = 0;

	BT_INFO("BlueFRITZ! USB device ready");

	kfree(buf);
	return 0;

error:
	kfree(buf);

	pipe = usb_sndctrlpipe(data->udev, 0);

	usb_control_msg(data->udev, pipe, USB_REQ_SET_CONFIGURATION,
				0, 0, 0, NULL, 0, USB_CTRL_SET_TIMEOUT);

	return err;
}