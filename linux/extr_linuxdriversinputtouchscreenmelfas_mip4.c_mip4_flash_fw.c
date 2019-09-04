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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mip4_ts {int /*<<< orphan*/  ppm_y; int /*<<< orphan*/  input; int /*<<< orphan*/  ppm_x; int /*<<< orphan*/  max_y; int /*<<< orphan*/  max_x; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  MIP4_BL_PACKET_SIZE ; 
 scalar_t__ MIP4_BL_PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_abs_set_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mip4_bl_enter (struct mip4_ts*) ; 
 int mip4_bl_exit (struct mip4_ts*) ; 
 int mip4_bl_get_address (struct mip4_ts*,int /*<<< orphan*/ *) ; 
 int mip4_bl_program_page (struct mip4_ts*,int,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int mip4_bl_verify_page (struct mip4_ts*,int,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mip4_power_off (struct mip4_ts*) ; 
 int /*<<< orphan*/  mip4_power_on (struct mip4_ts*) ; 
 int /*<<< orphan*/  mip4_query_device (struct mip4_ts*) ; 

__attribute__((used)) static int mip4_flash_fw(struct mip4_ts *ts,
			 const u8 *fw_data, u32 fw_size, u32 fw_offset)
{
	struct i2c_client *client = ts->client;
	int offset;
	u16 buf_addr;
	int error, error2;

	/* Enter bootloader mode */
	dev_dbg(&client->dev, "Entering bootloader mode\n");

	error = mip4_bl_enter(ts);
	if (error) {
		dev_err(&client->dev,
			"Failed to enter bootloader mode: %d\n",
			error);
		return error;
	}

	/* Read info */
	error = mip4_bl_get_address(ts, &buf_addr);
	if (error)
		goto exit_bl;

	/* Program & Verify */
	dev_dbg(&client->dev,
		"Program & Verify, page size: %d, packet size: %d\n",
		MIP4_BL_PAGE_SIZE, MIP4_BL_PACKET_SIZE);

	for (offset = fw_offset;
	     offset < fw_offset + fw_size;
	     offset += MIP4_BL_PAGE_SIZE) {
		/* Program */
		error = mip4_bl_program_page(ts, offset, fw_data + offset,
					     MIP4_BL_PAGE_SIZE, buf_addr);
		if (error)
			break;

		/* Verify */
		error = mip4_bl_verify_page(ts, offset, fw_data + offset,
					    MIP4_BL_PAGE_SIZE, buf_addr);
		if (error)
			break;
	}

exit_bl:
	/* Exit bootloader mode */
	dev_dbg(&client->dev, "Exiting bootloader mode\n");

	error2 = mip4_bl_exit(ts);
	if (error2) {
		dev_err(&client->dev,
			"Failed to exit bootloader mode: %d\n", error2);
		if (!error)
			error = error2;
	}

	/* Reset chip */
	mip4_power_off(ts);
	mip4_power_on(ts);

	mip4_query_device(ts);

	/* Refresh device parameters */
	input_set_abs_params(ts->input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_abs_params(ts->input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);
	input_set_abs_params(ts->input, ABS_X, 0, ts->max_x, 0, 0);
	input_set_abs_params(ts->input, ABS_Y, 0, ts->max_y, 0, 0);
	input_abs_set_res(ts->input, ABS_MT_POSITION_X, ts->ppm_x);
	input_abs_set_res(ts->input, ABS_MT_POSITION_Y, ts->ppm_y);
	input_abs_set_res(ts->input, ABS_X, ts->ppm_x);
	input_abs_set_res(ts->input, ABS_Y, ts->ppm_y);

	return error ? error : 0;
}