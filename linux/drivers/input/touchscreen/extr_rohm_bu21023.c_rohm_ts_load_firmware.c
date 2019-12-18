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
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct firmware {unsigned int size; int /*<<< orphan*/ * data; } ;
typedef  int s32 ;

/* Variables and functions */
 int CALIBRATION_DONE ; 
 int /*<<< orphan*/  COMMON_SETUP1 ; 
 int COMMON_SETUP1_DEFAULT ; 
 int COORD_UPDATE ; 
 int EIO ; 
 int /*<<< orphan*/  EX_ADDR_H ; 
 int /*<<< orphan*/  EX_ADDR_L ; 
 int /*<<< orphan*/  EX_WDAT ; 
 int /*<<< orphan*/  FIRMWARE_BLOCK_SIZE ; 
 unsigned int FIRMWARE_RETRY_MAX ; 
 int INT_ALL ; 
 int /*<<< orphan*/  INT_CLEAR ; 
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  INT_STATUS ; 
 int PROGRAM_LOAD_DONE ; 
 int SLEEP_IN ; 
 int SLEEP_OUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,struct device*) ; 

__attribute__((used)) static int rohm_ts_load_firmware(struct i2c_client *client,
				 const char *firmware_name)
{
	struct device *dev = &client->dev;
	const struct firmware *fw;
	s32 status;
	unsigned int offset, len, xfer_len;
	unsigned int retry = 0;
	int error, error2;

	error = request_firmware(&fw, firmware_name, dev);
	if (error) {
		dev_err(dev, "unable to retrieve firmware %s: %d\n",
			firmware_name, error);
		return error;
	}

	error = i2c_smbus_write_byte_data(client, INT_MASK,
					  COORD_UPDATE | CALIBRATION_DONE |
					  SLEEP_IN | SLEEP_OUT);
	if (error)
		goto out;

	do {
		if (retry) {
			dev_warn(dev, "retrying firmware load\n");

			/* settings for retry */
			error = i2c_smbus_write_byte_data(client, EX_WDAT, 0);
			if (error)
				goto out;
		}

		error = i2c_smbus_write_byte_data(client, EX_ADDR_H, 0);
		if (error)
			goto out;

		error = i2c_smbus_write_byte_data(client, EX_ADDR_L, 0);
		if (error)
			goto out;

		error = i2c_smbus_write_byte_data(client, COMMON_SETUP1,
						  COMMON_SETUP1_DEFAULT);
		if (error)
			goto out;

		/* firmware load to the device */
		offset = 0;
		len = fw->size;

		while (len) {
			xfer_len = min(FIRMWARE_BLOCK_SIZE, len);

			error = i2c_smbus_write_i2c_block_data(client, EX_WDAT,
						xfer_len, &fw->data[offset]);
			if (error)
				goto out;

			len -= xfer_len;
			offset += xfer_len;
		}

		/* check firmware load result */
		status = i2c_smbus_read_byte_data(client, INT_STATUS);
		if (status < 0) {
			error = status;
			goto out;
		}

		/* clear all interrupts */
		error = i2c_smbus_write_byte_data(client, INT_CLEAR, 0xff);
		if (error)
			goto out;

		if (status == PROGRAM_LOAD_DONE)
			break;

		error = -EIO;
	} while (++retry <= FIRMWARE_RETRY_MAX);

out:
	error2 = i2c_smbus_write_byte_data(client, INT_MASK, INT_ALL);

	release_firmware(fw);

	return error ? error : error2;
}