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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
struct ad2s90_state {int* rx; int /*<<< orphan*/  lock; int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IIO_ANGL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 struct ad2s90_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_read (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ad2s90_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	int ret;
	struct ad2s90_state *st = iio_priv(indio_dev);

	if (chan->type != IIO_ANGL)
		return -EINVAL;

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		/* 2 * Pi / 2^12 */
		*val = 6283; /* mV */
		*val2 = 12;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = spi_read(st->sdev, st->rx, 2);
		if (ret < 0) {
			mutex_unlock(&st->lock);
			return ret;
		}
		*val = (((u16)(st->rx[0])) << 4) | ((st->rx[1] & 0xF0) >> 4);

		mutex_unlock(&st->lock);

		return IIO_VAL_INT;
	default:
		break;
	}

	return -EINVAL;
}