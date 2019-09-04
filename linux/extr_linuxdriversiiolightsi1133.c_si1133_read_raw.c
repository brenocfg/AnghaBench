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
typedef  size_t u8 ;
struct si1133_data {size_t* adc_sens; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 135 
#define  IIO_CHAN_INFO_INT_TIME 134 
#define  IIO_CHAN_INFO_PROCESSED 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_INTENSITY 130 
#define  IIO_LIGHT 129 
#define  IIO_UVINDEX 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 size_t SI1133_ADCSENS_HSIG_SHIFT ; 
 size_t SI1133_ADCSENS_HW_GAIN_MASK ; 
 size_t SI1133_ADCSENS_SCALE_MASK ; 
 size_t SI1133_ADCSENS_SCALE_SHIFT ; 
 struct si1133_data* iio_priv (struct iio_dev*) ; 
 int si1133_get_lux (struct si1133_data*,int*) ; 
 int** si1133_int_time_table ; 
 int si1133_measure (struct si1133_data*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int si1133_read_raw(struct iio_dev *iio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct si1133_data *data = iio_priv(iio_dev);
	u8 adc_sens = data->adc_sens[0];
	int err;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_LIGHT:
			err = si1133_get_lux(data, val);
			if (err)
				return err;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			err = si1133_measure(data, chan, val);
			if (err)
				return err;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_HW_GAIN_MASK;

			*val = si1133_int_time_table[adc_sens][0];
			*val2 = si1133_int_time_table[adc_sens][1];
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens &= SI1133_ADCSENS_SCALE_MASK;
			adc_sens >>= SI1133_ADCSENS_SCALE_SHIFT;

			*val = BIT(adc_sens);

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_HARDWAREGAIN:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			adc_sens >>= SI1133_ADCSENS_HSIG_SHIFT;

			*val = adc_sens;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}