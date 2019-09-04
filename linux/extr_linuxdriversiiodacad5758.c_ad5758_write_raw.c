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
struct iio_chan_spec {int dummy; } ;
struct ad5758_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_DAC_INPUT ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int ad5758_spi_reg_write (struct ad5758_state*,int /*<<< orphan*/ ,int) ; 
 struct ad5758_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5758_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long info)
{
	struct ad5758_state *st = iio_priv(indio_dev);
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = ad5758_spi_reg_write(st, AD5758_DAC_INPUT, val);
		mutex_unlock(&st->lock);
		return ret;
	default:
		return -EINVAL;
	}
}