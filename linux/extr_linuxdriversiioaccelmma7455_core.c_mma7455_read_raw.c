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
struct mma7455_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int MMA7455_10BIT_SCALE ; 
 unsigned int MMA7455_CTL1_DFBW_MASK ; 
 int /*<<< orphan*/  MMA7455_REG_CTL1 ; 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct mma7455_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mma7455_drdy (struct mma7455_data*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma7455_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct mma7455_data *mma7455 = iio_priv(indio_dev);
	unsigned int reg;
	__le16 data;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;

		ret = mma7455_drdy(mma7455);
		if (ret)
			return ret;

		ret = regmap_bulk_read(mma7455->regmap, chan->address, &data,
				       sizeof(data));
		if (ret)
			return ret;

		*val = sign_extend32(le16_to_cpu(data), 9);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = MMA7455_10BIT_SCALE;

		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = regmap_read(mma7455->regmap, MMA7455_REG_CTL1, &reg);
		if (ret)
			return ret;

		if (reg & MMA7455_CTL1_DFBW_MASK)
			*val = 250;
		else
			*val = 125;

		return IIO_VAL_INT;
	}

	return -EINVAL;
}