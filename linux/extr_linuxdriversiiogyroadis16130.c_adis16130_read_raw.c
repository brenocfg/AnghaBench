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
typedef  int u32 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ANGL_VEL 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int adis16130_spi_read (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adis16130_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	int ret;
	u32 temp;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/* Take the iio_dev status lock */
		mutex_lock(&indio_dev->mlock);
		ret = adis16130_spi_read(indio_dev, chan->address, &temp);
		mutex_unlock(&indio_dev->mlock);
		if (ret)
			return ret;
		*val = temp;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			/* 0 degree = 838860, 250 degree = 14260608 */
			*val = 250;
			*val2 = 336440817; /* RAD_TO_DEGREE(14260608 - 8388608) */
			return IIO_VAL_FRACTIONAL;
		case IIO_TEMP:
			/* 0C = 8036283, 105C = 9516048 */
			*val = 105000;
			*val2 = 9516048 - 8036283;
			return IIO_VAL_FRACTIONAL;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			*val = -8388608;
			return IIO_VAL_INT;
		case IIO_TEMP:
			*val = -8036283;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	}

	return -EINVAL;
}