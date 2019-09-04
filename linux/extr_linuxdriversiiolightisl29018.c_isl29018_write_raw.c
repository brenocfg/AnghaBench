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
struct isl29018_chip {int calibscale; int ucalibscale; int /*<<< orphan*/  lock; scalar_t__ suspended; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_LIGHT ; 
 struct isl29018_chip* iio_priv (struct iio_dev*) ; 
 int isl29018_set_integration_time (struct isl29018_chip*,int) ; 
 int isl29018_set_scale (struct isl29018_chip*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isl29018_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val,
			      int val2,
			      long mask)
{
	struct isl29018_chip *chip = iio_priv(indio_dev);
	int ret = -EINVAL;

	mutex_lock(&chip->lock);
	if (chip->suspended) {
		ret = -EBUSY;
		goto write_done;
	}
	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_LIGHT) {
			chip->calibscale = val;
			chip->ucalibscale = val2;
			ret = 0;
		}
		break;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_LIGHT && !val)
			ret = isl29018_set_integration_time(chip, val2);
		break;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_LIGHT)
			ret = isl29018_set_scale(chip, val, val2);
		break;
	default:
		break;
	}

write_done:
	mutex_unlock(&chip->lock);

	return ret;
}