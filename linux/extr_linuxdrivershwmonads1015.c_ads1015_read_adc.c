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
typedef  int u16 ;
struct i2c_client {int dummy; } ;
struct ads1015_data {scalar_t__ id; int /*<<< orphan*/  update_lock; TYPE_1__* channel_data; } ;
struct TYPE_2__ {unsigned int pga; unsigned int data_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS1015_CONFIG ; 
 int /*<<< orphan*/  ADS1015_CONVERSION ; 
 unsigned int DIV_ROUND_UP (int,unsigned int const) ; 
 int EIO ; 
 scalar_t__ ads1115 ; 
 unsigned int* data_rate_table_1015 ; 
 unsigned int* data_rate_table_1115 ; 
 struct ads1015_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads1015_read_adc(struct i2c_client *client, unsigned int channel)
{
	u16 config;
	struct ads1015_data *data = i2c_get_clientdata(client);
	unsigned int pga = data->channel_data[channel].pga;
	unsigned int data_rate = data->channel_data[channel].data_rate;
	unsigned int conversion_time_ms;
	const unsigned int * const rate_table = data->id == ads1115 ?
		data_rate_table_1115 : data_rate_table_1015;
	int res;

	mutex_lock(&data->update_lock);

	/* get channel parameters */
	res = i2c_smbus_read_word_swapped(client, ADS1015_CONFIG);
	if (res < 0)
		goto err_unlock;
	config = res;
	conversion_time_ms = DIV_ROUND_UP(1000, rate_table[data_rate]);

	/* setup and start single conversion */
	config &= 0x001f;
	config |= (1 << 15) | (1 << 8);
	config |= (channel & 0x0007) << 12;
	config |= (pga & 0x0007) << 9;
	config |= (data_rate & 0x0007) << 5;

	res = i2c_smbus_write_word_swapped(client, ADS1015_CONFIG, config);
	if (res < 0)
		goto err_unlock;

	/* wait until conversion finished */
	msleep(conversion_time_ms);
	res = i2c_smbus_read_word_swapped(client, ADS1015_CONFIG);
	if (res < 0)
		goto err_unlock;
	config = res;
	if (!(config & (1 << 15))) {
		/* conversion not finished in time */
		res = -EIO;
		goto err_unlock;
	}

	res = i2c_smbus_read_word_swapped(client, ADS1015_CONVERSION);

err_unlock:
	mutex_unlock(&data->update_lock);
	return res;
}