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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int type; } ;
struct afe4403_data {int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_CURRENT 129 
#define  IIO_INTENSITY 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 unsigned int* afe4403_channel_leds ; 
 unsigned int* afe4403_channel_values ; 
 int afe4403_read (struct afe4403_data*,unsigned int,int*) ; 
 struct afe4403_data* iio_priv (struct iio_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int afe4403_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct afe4403_data *afe = iio_priv(indio_dev);
	unsigned int reg = afe4403_channel_values[chan->address];
	unsigned int field = afe4403_channel_leds[chan->address];
	int ret;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (mask) {
		case IIO_CHAN_INFO_RAW:
			ret = afe4403_read(afe, reg, val);
			if (ret)
				return ret;
			return IIO_VAL_INT;
		}
		break;
	case IIO_CURRENT:
		switch (mask) {
		case IIO_CHAN_INFO_RAW:
			ret = regmap_field_read(afe->fields[field], val);
			if (ret)
				return ret;
			return IIO_VAL_INT;
		case IIO_CHAN_INFO_SCALE:
			*val = 0;
			*val2 = 800000;
			return IIO_VAL_INT_PLUS_MICRO;
		}
		break;
	default:
		break;
	}

	return -EINVAL;
}