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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct adis16080_state {TYPE_1__* info; } ;
struct TYPE_2__ {int scale_val; int scale_val2; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
#define  IIO_ANGL_VEL 133 
#define  IIO_CHAN_INFO_OFFSET 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 int adis16080_read_sample (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 struct adis16080_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adis16080_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long mask)
{
	struct adis16080_state *st = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		ret = adis16080_read_sample(indio_dev, chan->address, val);
		mutex_unlock(&indio_dev->mlock);
		return ret ? ret : IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			*val = st->info->scale_val;
			*val2 = st->info->scale_val2;
			return IIO_VAL_FRACTIONAL;
		case IIO_VOLTAGE:
			/* VREF = 5V, 12 bits */
			*val = 5000;
			*val2 = 12;
			return IIO_VAL_FRACTIONAL_LOG2;
		case IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*val = 85000 - 25000;
			*val2 = 585;
			return IIO_VAL_FRACTIONAL;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_VOLTAGE:
			/* 2.5 V = 0 */
			*val = 2048;
			return IIO_VAL_INT;
		case IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*val = DIV_ROUND_CLOSEST(25 * 585, 85 - 25);
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		break;
	}

	return -EINVAL;
}