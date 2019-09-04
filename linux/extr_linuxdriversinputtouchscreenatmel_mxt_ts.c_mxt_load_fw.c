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
struct mxt_data {int in_bootloader; int /*<<< orphan*/  irq; int /*<<< orphan*/  bl_completion; } ;
struct firmware {unsigned int size; int* data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXT_BOOT_VALUE ; 
 int /*<<< orphan*/  MXT_COMMAND_RESET ; 
 int /*<<< orphan*/  MXT_FRAME_CRC_PASS ; 
 int /*<<< orphan*/  MXT_FW_RESET_TIME ; 
 unsigned int MXT_RESET_TIME ; 
 int /*<<< orphan*/  MXT_WAITING_BOOTLOAD_CMD ; 
 int /*<<< orphan*/  MXT_WAITING_FRAME_DATA ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct mxt_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int mxt_bootloader_write (struct mxt_data*,int*,unsigned int) ; 
 int mxt_check_bootloader (struct mxt_data*,int /*<<< orphan*/ ,int) ; 
 int mxt_check_firmware_format (struct device*,struct firmware const*) ; 
 int /*<<< orphan*/  mxt_free_input_device (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_free_object_table (struct mxt_data*) ; 
 int mxt_lookup_bootloader_address (struct mxt_data*,int /*<<< orphan*/ ) ; 
 int mxt_send_bootloader_cmd (struct mxt_data*,int) ; 
 int mxt_t6_command (struct mxt_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mxt_wait_for_completion (struct mxt_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,struct device*) ; 

__attribute__((used)) static int mxt_load_fw(struct device *dev, const char *fn)
{
	struct mxt_data *data = dev_get_drvdata(dev);
	const struct firmware *fw = NULL;
	unsigned int frame_size;
	unsigned int pos = 0;
	unsigned int retry = 0;
	unsigned int frame = 0;
	int ret;

	ret = request_firmware(&fw, fn, dev);
	if (ret) {
		dev_err(dev, "Unable to open firmware %s\n", fn);
		return ret;
	}

	/* Check for incorrect enc file */
	ret = mxt_check_firmware_format(dev, fw);
	if (ret)
		goto release_firmware;

	if (!data->in_bootloader) {
		/* Change to the bootloader mode */
		data->in_bootloader = true;

		ret = mxt_t6_command(data, MXT_COMMAND_RESET,
				     MXT_BOOT_VALUE, false);
		if (ret)
			goto release_firmware;

		msleep(MXT_RESET_TIME);

		/* Do not need to scan since we know family ID */
		ret = mxt_lookup_bootloader_address(data, 0);
		if (ret)
			goto release_firmware;

		mxt_free_input_device(data);
		mxt_free_object_table(data);
	} else {
		enable_irq(data->irq);
	}

	reinit_completion(&data->bl_completion);

	ret = mxt_check_bootloader(data, MXT_WAITING_BOOTLOAD_CMD, false);
	if (ret) {
		/* Bootloader may still be unlocked from previous attempt */
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, false);
		if (ret)
			goto disable_irq;
	} else {
		dev_info(dev, "Unlocking bootloader\n");

		/* Unlock bootloader */
		ret = mxt_send_bootloader_cmd(data, true);
		if (ret)
			goto disable_irq;
	}

	while (pos < fw->size) {
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, true);
		if (ret)
			goto disable_irq;

		frame_size = ((*(fw->data + pos) << 8) | *(fw->data + pos + 1));

		/* Take account of CRC bytes */
		frame_size += 2;

		/* Write one frame to device */
		ret = mxt_bootloader_write(data, fw->data + pos, frame_size);
		if (ret)
			goto disable_irq;

		ret = mxt_check_bootloader(data, MXT_FRAME_CRC_PASS, true);
		if (ret) {
			retry++;

			/* Back off by 20ms per retry */
			msleep(retry * 20);

			if (retry > 20) {
				dev_err(dev, "Retry count exceeded\n");
				goto disable_irq;
			}
		} else {
			retry = 0;
			pos += frame_size;
			frame++;
		}

		if (frame % 50 == 0)
			dev_dbg(dev, "Sent %d frames, %d/%zd bytes\n",
				frame, pos, fw->size);
	}

	/* Wait for flash. */
	ret = mxt_wait_for_completion(data, &data->bl_completion,
				      MXT_FW_RESET_TIME);
	if (ret)
		goto disable_irq;

	dev_dbg(dev, "Sent %d frames, %d bytes\n", frame, pos);

	/*
	 * Wait for device to reset. Some bootloader versions do not assert
	 * the CHG line after bootloading has finished, so ignore potential
	 * errors.
	 */
	mxt_wait_for_completion(data, &data->bl_completion, MXT_FW_RESET_TIME);

	data->in_bootloader = false;

disable_irq:
	disable_irq(data->irq);
release_firmware:
	release_firmware(fw);
	return ret;
}