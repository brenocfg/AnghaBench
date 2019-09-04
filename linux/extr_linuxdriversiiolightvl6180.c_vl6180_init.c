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
struct vl6180_data {int als_it_ms; int als_gain_milli; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VL6180_ALS_GAIN ; 
 int VL6180_ALS_GAIN_1 ; 
 int /*<<< orphan*/  VL6180_ALS_IT ; 
 int /*<<< orphan*/  VL6180_ALS_IT_100 ; 
 int VL6180_ALS_READY ; 
 int /*<<< orphan*/  VL6180_INTR_CONFIG ; 
 int /*<<< orphan*/  VL6180_MODEL_ID ; 
 int VL6180_MODEL_ID_VAL ; 
 int /*<<< orphan*/  VL6180_OUT_OF_RESET ; 
 int VL6180_RANGE_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int vl6180_hold (struct vl6180_data*,int) ; 
 int vl6180_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int vl6180_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int vl6180_write_word (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vl6180_init(struct vl6180_data *data)
{
	struct i2c_client *client = data->client;
	int ret;

	ret = vl6180_read_byte(client, VL6180_MODEL_ID);
	if (ret < 0)
		return ret;

	if (ret != VL6180_MODEL_ID_VAL) {
		dev_err(&client->dev, "invalid model ID %02x\n", ret);
		return -ENODEV;
	}

	ret = vl6180_hold(data, true);
	if (ret < 0)
		return ret;

	ret = vl6180_read_byte(client, VL6180_OUT_OF_RESET);
	if (ret < 0)
		return ret;

	/*
	 * Detect false reset condition here. This bit is always set when the
	 * system comes out of reset.
	 */
	if (ret != 0x01)
		dev_info(&client->dev, "device is not fresh out of reset\n");

	/* Enable ALS and Range ready interrupts */
	ret = vl6180_write_byte(client, VL6180_INTR_CONFIG,
				VL6180_ALS_READY | VL6180_RANGE_READY);
	if (ret < 0)
		return ret;

	/* ALS integration time: 100ms */
	data->als_it_ms = 100;
	ret = vl6180_write_word(client, VL6180_ALS_IT, VL6180_ALS_IT_100);
	if (ret < 0)
		return ret;

	/* ALS gain: 1 */
	data->als_gain_milli = 1000;
	ret = vl6180_write_byte(client, VL6180_ALS_GAIN, VL6180_ALS_GAIN_1);
	if (ret < 0)
		return ret;

	ret = vl6180_write_byte(client, VL6180_OUT_OF_RESET, 0x00);
	if (ret < 0)
		return ret;

	return vl6180_hold(data, false);
}