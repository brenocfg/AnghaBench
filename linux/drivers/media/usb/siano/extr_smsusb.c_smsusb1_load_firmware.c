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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int default_mode; } ;

/* Variables and functions */
 int DEVICE_MODE_DVBT ; 
 int DEVICE_MODE_DVBT_BDA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* sms_get_board (int) ; 
 char* sms_get_fw_name (int,int) ; 
 char** smsusb1_fw_lkup ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int smsusb1_load_firmware(struct usb_device *udev, int id, int board_id)
{
	const struct firmware *fw;
	u8 *fw_buffer;
	int rc, dummy;
	char *fw_filename;

	if (id < 0)
		id = sms_get_board(board_id)->default_mode;

	if (id < DEVICE_MODE_DVBT || id > DEVICE_MODE_DVBT_BDA) {
		pr_err("invalid firmware id specified %d\n", id);
		return -EINVAL;
	}

	fw_filename = sms_get_fw_name(id, board_id);

	rc = request_firmware(&fw, fw_filename, &udev->dev);
	if (rc < 0) {
		pr_warn("failed to open '%s' mode %d, trying again with default firmware\n",
			fw_filename, id);

		fw_filename = smsusb1_fw_lkup[id];
		rc = request_firmware(&fw, fw_filename, &udev->dev);
		if (rc < 0) {
			pr_warn("failed to open '%s' mode %d\n",
				 fw_filename, id);

			return rc;
		}
	}

	fw_buffer = kmalloc(fw->size, GFP_KERNEL);
	if (fw_buffer) {
		memcpy(fw_buffer, fw->data, fw->size);

		rc = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 2),
				  fw_buffer, fw->size, &dummy, 1000);

		pr_debug("sent %zu(%d) bytes, rc %d\n", fw->size, dummy, rc);

		kfree(fw_buffer);
	} else {
		pr_err("failed to allocate firmware buffer\n");
		rc = -ENOMEM;
	}
	pr_debug("read FW %s, size=%zu\n", fw_filename, fw->size);

	release_firmware(fw);

	return rc;
}