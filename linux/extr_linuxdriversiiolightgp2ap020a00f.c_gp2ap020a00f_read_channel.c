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
struct iio_chan_spec {int scan_index; int /*<<< orphan*/  address; } ;
struct gp2ap020a00f_data {TYPE_1__* client; } ;
typedef  enum gp2ap020a00f_cmd { ____Placeholder_gp2ap020a00f_cmd } gp2ap020a00f_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int GP2AP020A00F_CMD_READ_RAW_CLEAR ; 
 int GP2AP020A00F_CMD_READ_RAW_IR ; 
 int GP2AP020A00F_CMD_READ_RAW_PROXIMITY ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_SHUTDOWN ; 
#define  GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR 130 
#define  GP2AP020A00F_SCAN_MODE_LIGHT_IR 129 
#define  GP2AP020A00F_SCAN_MODE_PROXIMITY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gp2ap020a00f_exec_cmd (struct gp2ap020a00f_data*,int) ; 
 int /*<<< orphan*/  gp2ap020a00f_output_to_lux (struct gp2ap020a00f_data*,int*) ; 
 int gp2ap020a00f_read_output (struct gp2ap020a00f_data*,int /*<<< orphan*/ ,int*) ; 
 int gp2ap020a00f_set_operation_mode (struct gp2ap020a00f_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp2ap020a00f_read_channel(struct gp2ap020a00f_data *data,
				struct iio_chan_spec const *chan, int *val)
{
	enum gp2ap020a00f_cmd cmd;
	int err;

	switch (chan->scan_index) {
	case GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR:
		cmd = GP2AP020A00F_CMD_READ_RAW_CLEAR;
		break;
	case GP2AP020A00F_SCAN_MODE_LIGHT_IR:
		cmd = GP2AP020A00F_CMD_READ_RAW_IR;
		break;
	case GP2AP020A00F_SCAN_MODE_PROXIMITY:
		cmd = GP2AP020A00F_CMD_READ_RAW_PROXIMITY;
		break;
	default:
		return -EINVAL;
	}

	err = gp2ap020a00f_exec_cmd(data, cmd);
	if (err < 0) {
		dev_err(&data->client->dev,
			"gp2ap020a00f_exec_cmd failed\n");
		goto error_ret;
	}

	err = gp2ap020a00f_read_output(data, chan->address, val);
	if (err < 0)
		dev_err(&data->client->dev,
			"gp2ap020a00f_read_output failed\n");

	err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
	if (err < 0)
		dev_err(&data->client->dev,
			"Failed to shut down the device.\n");

	if (cmd == GP2AP020A00F_CMD_READ_RAW_CLEAR ||
	    cmd == GP2AP020A00F_CMD_READ_RAW_IR)
		gp2ap020a00f_output_to_lux(data, val);

error_ret:
	return err;
}