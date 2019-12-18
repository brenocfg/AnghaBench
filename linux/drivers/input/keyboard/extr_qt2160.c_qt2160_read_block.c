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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_master_recv (struct i2c_client*,int*,unsigned int) ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 

__attribute__((used)) static int qt2160_read_block(struct i2c_client *client,
			     u8 inireg, u8 *buffer, unsigned int count)
{
	int error, idx = 0;

	/*
	 * Can't use SMBus block data read. Check for I2C functionality to speed
	 * things up whenever possible. Otherwise we will be forced to read
	 * sequentially.
	 */
	if (i2c_check_functionality(client->adapter, I2C_FUNC_I2C))	{

		error = i2c_smbus_write_byte(client, inireg + idx);
		if (error) {
			dev_err(&client->dev,
				"couldn't send request. Returned %d\n", error);
			return error;
		}

		error = i2c_master_recv(client, buffer, count);
		if (error != count) {
			dev_err(&client->dev,
				"couldn't read registers. Returned %d bytes\n", error);
			return error;
		}
	} else {

		while (count--) {
			int data;

			error = i2c_smbus_write_byte(client, inireg + idx);
			if (error) {
				dev_err(&client->dev,
					"couldn't send request. Returned %d\n", error);
				return error;
			}

			data = i2c_smbus_read_byte(client);
			if (data < 0) {
				dev_err(&client->dev,
					"couldn't read register. Returned %d\n", data);
				return data;
			}

			buffer[idx++] = data;
		}
	}

	return 0;
}