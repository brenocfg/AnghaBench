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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct as10x_bus_adapter_t {struct usb_device* usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_FW_PKT_SIZE ; 
 char* as102_dt_fw1 ; 
 char* as102_dt_fw2 ; 
 int as102_firmware_upload (struct as10x_bus_adapter_t*,unsigned char*,struct firmware const*) ; 
 char* as102_st_fw1 ; 
 char* as102_st_fw2 ; 
 scalar_t__ dual_tuner ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

int as102_fw_upload(struct as10x_bus_adapter_t *bus_adap)
{
	int errno = -EFAULT;
	const struct firmware *firmware = NULL;
	unsigned char *cmd_buf = NULL;
	const char *fw1, *fw2;
	struct usb_device *dev = bus_adap->usb_dev;

	/* select fw file to upload */
	if (dual_tuner) {
		fw1 = as102_dt_fw1;
		fw2 = as102_dt_fw2;
	} else {
		fw1 = as102_st_fw1;
		fw2 = as102_st_fw2;
	}

	/* allocate buffer to store firmware upload command and data */
	cmd_buf = kzalloc(MAX_FW_PKT_SIZE, GFP_KERNEL);
	if (cmd_buf == NULL) {
		errno = -ENOMEM;
		goto error;
	}

	/* request kernel to locate firmware file: part1 */
	errno = request_firmware(&firmware, fw1, &dev->dev);
	if (errno < 0) {
		pr_err("%s: unable to locate firmware file: %s\n",
		       DRIVER_NAME, fw1);
		goto error;
	}

	/* initiate firmware upload */
	errno = as102_firmware_upload(bus_adap, cmd_buf, firmware);
	if (errno < 0) {
		pr_err("%s: error during firmware upload part1\n",
		       DRIVER_NAME);
		goto error;
	}

	pr_info("%s: firmware: %s loaded with success\n",
		DRIVER_NAME, fw1);
	release_firmware(firmware);
	firmware = NULL;

	/* wait for boot to complete */
	mdelay(100);

	/* request kernel to locate firmware file: part2 */
	errno = request_firmware(&firmware, fw2, &dev->dev);
	if (errno < 0) {
		pr_err("%s: unable to locate firmware file: %s\n",
		       DRIVER_NAME, fw2);
		goto error;
	}

	/* initiate firmware upload */
	errno = as102_firmware_upload(bus_adap, cmd_buf, firmware);
	if (errno < 0) {
		pr_err("%s: error during firmware upload part2\n",
		       DRIVER_NAME);
		goto error;
	}

	pr_info("%s: firmware: %s loaded with success\n",
		DRIVER_NAME, fw2);
error:
	kfree(cmd_buf);
	release_firmware(firmware);

	return errno;
}