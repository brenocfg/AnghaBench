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
struct icn8505_data {int /*<<< orphan*/  firmware_name; TYPE_1__* client; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int MAX_FW_UPLOAD_TRIES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int icn8505_read_reg_silent (struct icn8505_data*,int) ; 
 int icn8505_try_fw_upload (struct icn8505_data*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int icn8505_upload_fw(struct icn8505_data *icn8505)
{
	struct device *dev = &icn8505->client->dev;
	const struct firmware *fw;
	int i, error;

	/*
	 * Always load the firmware, even if we don't need it at boot, we
	 * we may need it at resume. Having loaded it once will make the
	 * firmware class code cache it at suspend/resume.
	 */
	error = request_firmware(&fw, icn8505->firmware_name, dev);
	if (error) {
		dev_err(dev, "Firmware request error %d\n", error);
		return error;
	}

	/* Check if the controller is not already up and running */
	if (icn8505_read_reg_silent(icn8505, 0x000a) == 0x85)
		goto success;

	for (i = 1; i <= MAX_FW_UPLOAD_TRIES; i++) {
		error = icn8505_try_fw_upload(icn8505, fw);
		if (!error)
			goto success;

		dev_err(dev, "Failed to upload firmware: %d (attempt %d/%d)\n",
			error, i, MAX_FW_UPLOAD_TRIES);
		usleep_range(2000, 5000);
	}

success:
	release_firmware(fw);
	return error;
}