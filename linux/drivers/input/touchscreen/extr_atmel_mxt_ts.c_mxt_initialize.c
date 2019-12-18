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
struct mxt_data {int in_bootloader; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MXT_CFG_NAME ; 
 int /*<<< orphan*/  MXT_FW_RESET_TIME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int mxt_acquire_irq (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_config_cb ; 
 int mxt_probe_bootloader (struct mxt_data*,int) ; 
 int mxt_read_info_block (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_send_bootloader_cmd (struct mxt_data*,int) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mxt_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxt_initialize(struct mxt_data *data)
{
	struct i2c_client *client = data->client;
	int recovery_attempts = 0;
	int error;

	while (1) {
		error = mxt_read_info_block(data);
		if (!error)
			break;

		/* Check bootloader state */
		error = mxt_probe_bootloader(data, false);
		if (error) {
			dev_info(&client->dev, "Trying alternate bootloader address\n");
			error = mxt_probe_bootloader(data, true);
			if (error) {
				/* Chip is not in appmode or bootloader mode */
				return error;
			}
		}

		/* OK, we are in bootloader, see if we can recover */
		if (++recovery_attempts > 1) {
			dev_err(&client->dev, "Could not recover from bootloader mode\n");
			/*
			 * We can reflash from this state, so do not
			 * abort initialization.
			 */
			data->in_bootloader = true;
			return 0;
		}

		/* Attempt to exit bootloader into app mode */
		mxt_send_bootloader_cmd(data, false);
		msleep(MXT_FW_RESET_TIME);
	}

	error = mxt_acquire_irq(data);
	if (error)
		return error;

	error = request_firmware_nowait(THIS_MODULE, true, MXT_CFG_NAME,
					&client->dev, GFP_KERNEL, data,
					mxt_config_cb);
	if (error) {
		dev_err(&client->dev, "Failed to invoke firmware loader: %d\n",
			error);
		return error;
	}

	return 0;
}