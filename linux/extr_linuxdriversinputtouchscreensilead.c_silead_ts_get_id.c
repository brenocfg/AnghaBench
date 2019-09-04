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
struct silead_ts_data {int /*<<< orphan*/  chip_id; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  chip_id ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SILEAD_REG_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct silead_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int silead_ts_get_id(struct i2c_client *client)
{
	struct silead_ts_data *data = i2c_get_clientdata(client);
	__le32 chip_id;
	int error;

	error = i2c_smbus_read_i2c_block_data(client, SILEAD_REG_ID,
					      sizeof(chip_id), (u8 *)&chip_id);
	if (error < 0) {
		dev_err(&client->dev, "Chip ID read error %d\n", error);
		return error;
	}

	data->chip_id = le32_to_cpu(chip_id);
	dev_info(&client->dev, "Silead chip ID: 0x%8X", data->chip_id);

	return 0;
}