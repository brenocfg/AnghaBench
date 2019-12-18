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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct dmard06_data {int /*<<< orphan*/  chip_id; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMARD05_AXIS_SCALE_VAL ; 
 int DMARD06_AXIS_SCALE_VAL ; 
 int /*<<< orphan*/  DMARD06_CHIP_ID ; 
 int /*<<< orphan*/  DMARD06_SIGN_BIT ; 
 int DMARD06_TEMP_CENTER_VAL ; 
 int EINVAL ; 
#define  IIO_ACCEL 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct dmard06_data* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmard06_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct dmard06_data *dmard06 = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_read_byte_data(dmard06->client,
					       chan->address);
		if (ret < 0) {
			dev_err(&dmard06->client->dev,
				"Error reading data: %d\n", ret);
			return ret;
		}

		*val = sign_extend32(ret, DMARD06_SIGN_BIT);

		if (dmard06->chip_id == DMARD06_CHIP_ID)
			*val = *val >> 1;

		switch (chan->type) {
		case IIO_ACCEL:
			return IIO_VAL_INT;
		case IIO_TEMP:
			if (dmard06->chip_id != DMARD06_CHIP_ID)
				*val = *val / 2;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*val = DMARD06_TEMP_CENTER_VAL;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ACCEL:
			*val = 0;
			if (dmard06->chip_id == DMARD06_CHIP_ID)
				*val2 = DMARD06_AXIS_SCALE_VAL;
			else
				*val2 = DMARD05_AXIS_SCALE_VAL;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}