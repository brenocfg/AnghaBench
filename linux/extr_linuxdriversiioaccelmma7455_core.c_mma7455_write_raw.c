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
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int MMA7455_10BIT_SCALE ; 
 int MMA7455_CTL1_DFBW_125HZ ; 
 int MMA7455_CTL1_DFBW_62_5HZ ; 
 int /*<<< orphan*/  MMA7455_CTL1_DFBW_MASK ; 
 int /*<<< orphan*/  MMA7455_REG_CTL1 ; 
 struct mma7455_data* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma7455_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct mma7455_data *mma7455 = iio_priv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		if (val == 250 && val2 == 0)
			i = MMA7455_CTL1_DFBW_125HZ;
		else if (val == 125 && val2 == 0)
			i = MMA7455_CTL1_DFBW_62_5HZ;
		else
			return -EINVAL;

		return regmap_update_bits(mma7455->regmap, MMA7455_REG_CTL1,
					  MMA7455_CTL1_DFBW_MASK, i);

	case IIO_CHAN_INFO_SCALE:
		/* In 10-bit mode there is only one scale available */
		if (val == 0 && val2 == MMA7455_10BIT_SCALE)
			return 0;
		break;
	}

	return -EINVAL;
}