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
struct ms5611_state {int /*<<< orphan*/  lock; struct ms5611_osr const* pressure_osr; struct ms5611_osr const* temp_osr; } ;
struct ms5611_osr {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_OVERSAMPLING_RATIO ; 
 scalar_t__ IIO_PRESSURE ; 
 scalar_t__ IIO_TEMP ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ms5611_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ms5611_avail_pressure_osr ; 
 int /*<<< orphan*/  ms5611_avail_temp_osr ; 
 struct ms5611_osr* ms5611_find_osr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ms5611_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct ms5611_state *st = iio_priv(indio_dev);
	const struct ms5611_osr *osr = NULL;
	int ret;

	if (mask != IIO_CHAN_INFO_OVERSAMPLING_RATIO)
		return -EINVAL;

	if (chan->type == IIO_TEMP)
		osr = ms5611_find_osr(val, ms5611_avail_temp_osr,
				      ARRAY_SIZE(ms5611_avail_temp_osr));
	else if (chan->type == IIO_PRESSURE)
		osr = ms5611_find_osr(val, ms5611_avail_pressure_osr,
				      ARRAY_SIZE(ms5611_avail_pressure_osr));
	if (!osr)
		return -EINVAL;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;

	mutex_lock(&st->lock);

	if (chan->type == IIO_TEMP)
		st->temp_osr = osr;
	else
		st->pressure_osr = osr;

	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);

	return 0;
}