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
struct iio_chan_spec {int type; int /*<<< orphan*/  address; } ;
struct i2c_client {int dummy; } ;
struct cm36651_data {struct i2c_client* ps_client; int /*<<< orphan*/  flags; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM36651_ALS_DISABLE ; 
 int /*<<< orphan*/  CM36651_CS_CONF1 ; 
 int /*<<< orphan*/  CM36651_PROXIMITY_EV_EN ; 
 int /*<<< orphan*/  CM36651_PS_CONF1 ; 
 int /*<<< orphan*/  CM36651_PS_DISABLE ; 
 int EINVAL ; 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int i2c_smbus_read_byte (struct i2c_client*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm36651_read_output(struct cm36651_data *cm36651,
				struct iio_chan_spec const *chan, int *val)
{
	struct i2c_client *client = cm36651->client;
	int ret = -EINVAL;

	switch (chan->type) {
	case IIO_LIGHT:
		*val = i2c_smbus_read_word_data(client, chan->address);
		if (*val < 0)
			return ret;

		ret = i2c_smbus_write_byte_data(client, CM36651_CS_CONF1,
							CM36651_ALS_DISABLE);
		if (ret < 0)
			return ret;

		ret = IIO_VAL_INT;
		break;
	case IIO_PROXIMITY:
		*val = i2c_smbus_read_byte(cm36651->ps_client);
		if (*val < 0)
			return ret;

		if (!test_bit(CM36651_PROXIMITY_EV_EN, &cm36651->flags)) {
			ret = i2c_smbus_write_byte_data(cm36651->ps_client,
					CM36651_PS_CONF1, CM36651_PS_DISABLE);
			if (ret < 0)
				return ret;
		}

		ret = IIO_VAL_INT;
		break;
	default:
		break;
	}

	return ret;
}