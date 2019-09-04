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
struct envelope {int high; int dac_max; int invert; int level; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  dac; int /*<<< orphan*/  done; int /*<<< orphan*/  low; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  envelope_detector_setup_compare (struct envelope*) ; 
 struct envelope* iio_priv (struct iio_dev*) ; 
 int iio_read_channel_scale (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int envelope_detector_read_raw(struct iio_dev *indio_dev,
				      struct iio_chan_spec const *chan,
				      int *val, int *val2, long mask)
{
	struct envelope *env = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		/*
		 * When invert is active, start with high=max+1 and low=0
		 * since we will end up with the low value when the
		 * termination criteria is fulfilled (rounding down). And
		 * start with high=max and low=-1 when invert is not active
		 * since we will end up with the high value in that case.
		 * This ensures that the returned value in both cases are
		 * in the same range as the DAC and is a value that has not
		 * triggered the comparator.
		 */
		mutex_lock(&env->read_lock);
		env->high = env->dac_max + env->invert;
		env->low = -1 + env->invert;
		envelope_detector_setup_compare(env);
		wait_for_completion(&env->done);
		if (env->level < 0) {
			ret = env->level;
			goto err_unlock;
		}
		*val = env->invert ? env->dac_max - env->level : env->level;
		mutex_unlock(&env->read_lock);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		return iio_read_channel_scale(env->dac, val, val2);
	}

	return -EINVAL;

err_unlock:
	mutex_unlock(&env->read_lock);
	return ret;
}