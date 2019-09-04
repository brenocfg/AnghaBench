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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; } ;
struct dmard10_data {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DMARD10_REG_STADR ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int dmard10_nscale ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct dmard10_data* iio_priv (struct iio_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int dmard10_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct dmard10_data *data = iio_priv(indio_dev);
	__le16 buf[4];
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/*
		 * Read 8 bytes starting at the REG_STADR register, trying to
		 * read the individual X, Y, Z registers will always read 0.
		 */
		ret = i2c_smbus_read_i2c_block_data(data->client,
						    DMARD10_REG_STADR,
						    sizeof(buf), (u8 *)buf);
		if (ret < 0)
			return ret;
		ret = le16_to_cpu(buf[chan->address]);
		*val = sign_extend32(ret, 12);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = dmard10_nscale;
		return IIO_VAL_INT_PLUS_NANO;
	default:
		return -EINVAL;
	}
}