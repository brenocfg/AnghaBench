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
struct max5821_data {struct i2c_client* client; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 struct max5821_data* iio_priv (struct iio_dev*) ; 
 int* max5821_load_dac_command ; 

__attribute__((used)) static int max5821_set_value(struct iio_dev *indio_dev,
			     int val, int channel)
{
	struct max5821_data *data = iio_priv(indio_dev);
	struct i2c_client *client = data->client;
	u8 outbuf[2];
	int ret;

	if ((val < 0) || (val > 1023))
		return -EINVAL;

	if ((channel != 0) && (channel != 1))
		return -EINVAL;

	outbuf[0] = max5821_load_dac_command[channel];
	outbuf[0] |= val >> 6;
	outbuf[1] = (val & 0x3f) << 2;

	ret = i2c_master_send(client, outbuf, 2);
	if (ret < 0)
		return ret;
	else if (ret != 2)
		return -EIO;
	else
		return 0;
}