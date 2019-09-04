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
struct si1133_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 132 
#define  IIO_CHAN_INFO_INT_TIME 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_INTENSITY 129 
#define  IIO_UVINDEX 128 
 int /*<<< orphan*/  SI1133_ADCSENS_HSIG_MASK ; 
 int /*<<< orphan*/  SI1133_ADCSENS_HSIG_SHIFT ; 
 int /*<<< orphan*/  SI1133_ADCSENS_SCALE_MASK ; 
 int /*<<< orphan*/  SI1133_ADCSENS_SCALE_SHIFT ; 
 struct si1133_data* iio_priv (struct iio_dev*) ; 
 int si1133_scale_to_swgain (int,int) ; 
 int si1133_set_integration_time (struct si1133_data*,int /*<<< orphan*/ ,int,int) ; 
 int si1133_update_adcsens (struct si1133_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si1133_write_raw(struct iio_dev *iio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct si1133_data *data = iio_priv(iio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			val = si1133_scale_to_swgain(val, val2);
			if (val < 0)
				return val;

			return si1133_update_adcsens(data,
						     SI1133_ADCSENS_SCALE_MASK,
						     SI1133_ADCSENS_SCALE_SHIFT,
						     val);
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_INT_TIME:
		return si1133_set_integration_time(data, 0, val, val2);
	case IIO_CHAN_INFO_HARDWAREGAIN:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_UVINDEX:
			if (val != 0 && val != 1)
				return -EINVAL;

			return si1133_update_adcsens(data,
						     SI1133_ADCSENS_HSIG_MASK,
						     SI1133_ADCSENS_HSIG_SHIFT,
						     val);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}