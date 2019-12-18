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
struct iio_chan_spec {int type; int address; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cm36651_data {int* cs_int_time; int ps_int_time; struct i2c_client* ps_client; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM36651_CS_CONF3 ; 
 int CM36651_CS_IT1 ; 
 int CM36651_CS_IT2 ; 
 int CM36651_CS_IT3 ; 
 int CM36651_CS_IT4 ; 
 int /*<<< orphan*/  CM36651_PS_CONF1 ; 
 int CM36651_PS_IT1 ; 
 int CM36651_PS_IT2 ; 
 int CM36651_PS_IT3 ; 
 int CM36651_PS_IT4 ; 
 int EINVAL ; 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cm36651_write_int_time(struct cm36651_data *cm36651,
				struct iio_chan_spec const *chan, int val)
{
	struct i2c_client *client = cm36651->client;
	struct i2c_client *ps_client = cm36651->ps_client;
	int int_time, ret;

	switch (chan->type) {
	case IIO_LIGHT:
		if (val == 80000)
			int_time = CM36651_CS_IT1;
		else if (val == 160000)
			int_time = CM36651_CS_IT2;
		else if (val == 320000)
			int_time = CM36651_CS_IT3;
		else if (val == 640000)
			int_time = CM36651_CS_IT4;
		else
			return -EINVAL;

		ret = i2c_smbus_write_byte_data(client, CM36651_CS_CONF3,
					   int_time >> 2 * (chan->address));
		if (ret < 0) {
			dev_err(&client->dev, "CS integration time write failed\n");
			return ret;
		}
		cm36651->cs_int_time[chan->address] = int_time;
		break;
	case IIO_PROXIMITY:
		if (val == 320)
			int_time = CM36651_PS_IT1;
		else if (val == 420)
			int_time = CM36651_PS_IT2;
		else if (val == 520)
			int_time = CM36651_PS_IT3;
		else if (val == 640)
			int_time = CM36651_PS_IT4;
		else
			return -EINVAL;

		ret = i2c_smbus_write_byte_data(ps_client,
						CM36651_PS_CONF1, int_time);
		if (ret < 0) {
			dev_err(&client->dev, "PS integration time write failed\n");
			return ret;
		}
		cm36651->ps_int_time = int_time;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}