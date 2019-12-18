#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct ds2482_data {int w1_count; TYPE_1__* w1_ch; int /*<<< orphan*/  access_lock; struct i2c_client* client; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_pullup; int /*<<< orphan*/  reset_bus; int /*<<< orphan*/  triplet; int /*<<< orphan*/  touch_bit; int /*<<< orphan*/  write_byte; int /*<<< orphan*/  read_byte; TYPE_1__* data; } ;
struct TYPE_4__ {int channel; TYPE_2__ w1_bm; struct ds2482_data* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2482_CMD_RESET ; 
 int /*<<< orphan*/  DS2482_CMD_WRITE_CONFIG ; 
 int DS2482_REG_STS_LL ; 
 int DS2482_REG_STS_RST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ds2482_calculate_config (int) ; 
 scalar_t__ ds2482_send_cmd (struct ds2482_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2482_send_cmd_data (struct ds2482_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ds2482_set_channel (struct ds2482_data*,int) ; 
 int /*<<< orphan*/  ds2482_w1_read_byte ; 
 int /*<<< orphan*/  ds2482_w1_reset_bus ; 
 int /*<<< orphan*/  ds2482_w1_set_pullup ; 
 int /*<<< orphan*/  ds2482_w1_touch_bit ; 
 int /*<<< orphan*/  ds2482_w1_triplet ; 
 int /*<<< orphan*/  ds2482_w1_write_byte ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ds2482_data*) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct ds2482_data*) ; 
 struct ds2482_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int w1_add_master_device (TYPE_2__*) ; 
 int /*<<< orphan*/  w1_remove_master_device (TYPE_2__*) ; 

__attribute__((used)) static int ds2482_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ds2482_data *data;
	int err = -ENODEV;
	int temp1;
	int idx;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_BYTE))
		return -ENODEV;

	if (!(data = kzalloc(sizeof(struct ds2482_data), GFP_KERNEL))) {
		err = -ENOMEM;
		goto exit;
	}

	data->client = client;
	i2c_set_clientdata(client, data);

	/* Reset the device (sets the read_ptr to status) */
	if (ds2482_send_cmd(data, DS2482_CMD_RESET) < 0) {
		dev_warn(&client->dev, "DS2482 reset failed.\n");
		goto exit_free;
	}

	/* Sleep at least 525ns to allow the reset to complete */
	ndelay(525);

	/* Read the status byte - only reset bit and line should be set */
	temp1 = i2c_smbus_read_byte(client);
	if (temp1 != (DS2482_REG_STS_LL | DS2482_REG_STS_RST)) {
		dev_warn(&client->dev, "DS2482 reset status "
			 "0x%02X - not a DS2482\n", temp1);
		goto exit_free;
	}

	/* Detect the 8-port version */
	data->w1_count = 1;
	if (ds2482_set_channel(data, 7) == 0)
		data->w1_count = 8;

	/* Set all config items to 0 (off) */
	ds2482_send_cmd_data(data, DS2482_CMD_WRITE_CONFIG,
		ds2482_calculate_config(0x00));

	mutex_init(&data->access_lock);

	/* Register 1-wire interface(s) */
	for (idx = 0; idx < data->w1_count; idx++) {
		data->w1_ch[idx].pdev = data;
		data->w1_ch[idx].channel = idx;

		/* Populate all the w1 bus master stuff */
		data->w1_ch[idx].w1_bm.data       = &data->w1_ch[idx];
		data->w1_ch[idx].w1_bm.read_byte  = ds2482_w1_read_byte;
		data->w1_ch[idx].w1_bm.write_byte = ds2482_w1_write_byte;
		data->w1_ch[idx].w1_bm.touch_bit  = ds2482_w1_touch_bit;
		data->w1_ch[idx].w1_bm.triplet    = ds2482_w1_triplet;
		data->w1_ch[idx].w1_bm.reset_bus  = ds2482_w1_reset_bus;
		data->w1_ch[idx].w1_bm.set_pullup = ds2482_w1_set_pullup;

		err = w1_add_master_device(&data->w1_ch[idx].w1_bm);
		if (err) {
			data->w1_ch[idx].pdev = NULL;
			goto exit_w1_remove;
		}
	}

	return 0;

exit_w1_remove:
	for (idx = 0; idx < data->w1_count; idx++) {
		if (data->w1_ch[idx].pdev != NULL)
			w1_remove_master_device(&data->w1_ch[idx].w1_bm);
	}
exit_free:
	kfree(data);
exit:
	return err;
}