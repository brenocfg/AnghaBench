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
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  dev; } ;
struct eeprom_data {int valid; int* data; int /*<<< orphan*/  update_lock; scalar_t__* last_updated; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eeprom_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int,int,int*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void eeprom_update_client(struct i2c_client *client, u8 slice)
{
	struct eeprom_data *data = i2c_get_clientdata(client);
	int i;

	mutex_lock(&data->update_lock);

	if (!(data->valid & (1 << slice)) ||
	    time_after(jiffies, data->last_updated[slice] + 300 * HZ)) {
		dev_dbg(&client->dev, "Starting eeprom update, slice %u\n", slice);

		if (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
			for (i = slice << 5; i < (slice + 1) << 5; i += 32)
				if (i2c_smbus_read_i2c_block_data(client, i,
							32, data->data + i)
							!= 32)
					goto exit;
		} else {
			for (i = slice << 5; i < (slice + 1) << 5; i += 2) {
				int word = i2c_smbus_read_word_data(client, i);
				if (word < 0)
					goto exit;
				data->data[i] = word & 0xff;
				data->data[i + 1] = word >> 8;
			}
		}
		data->last_updated[slice] = jiffies;
		data->valid |= (1 << slice);
	}
exit:
	mutex_unlock(&data->update_lock);
}