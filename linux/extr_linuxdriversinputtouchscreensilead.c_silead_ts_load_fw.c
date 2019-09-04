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
struct silead_ts_data {int /*<<< orphan*/  fw_name; } ;
struct silead_fw_data {int /*<<< orphan*/  val; int /*<<< orphan*/  offset; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct silead_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static int silead_ts_load_fw(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct silead_ts_data *data = i2c_get_clientdata(client);
	unsigned int fw_size, i;
	const struct firmware *fw;
	struct silead_fw_data *fw_data;
	int error;

	dev_dbg(dev, "Firmware file name: %s", data->fw_name);

	error = request_firmware(&fw, data->fw_name, dev);
	if (error) {
		dev_err(dev, "Firmware request error %d\n", error);
		return error;
	}

	fw_size = fw->size / sizeof(*fw_data);
	fw_data = (struct silead_fw_data *)fw->data;

	for (i = 0; i < fw_size; i++) {
		error = i2c_smbus_write_i2c_block_data(client,
						       fw_data[i].offset,
						       4,
						       (u8 *)&fw_data[i].val);
		if (error) {
			dev_err(dev, "Firmware load error %d\n", error);
			break;
		}
	}

	release_firmware(fw);
	return error ?: 0;
}