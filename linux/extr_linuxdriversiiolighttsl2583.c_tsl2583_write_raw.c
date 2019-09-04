#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int als_gain_trim; unsigned int als_gain; int als_time; } ;
struct tsl2583_chip {int /*<<< orphan*/  als_mutex; TYPE_1__ als_settings; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int mean; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int /*<<< orphan*/  IIO_LIGHT ; 
 TYPE_2__* gainadj ; 
 struct tsl2583_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsl2583_set_als_gain (struct tsl2583_chip*) ; 
 int tsl2583_set_als_time (struct tsl2583_chip*) ; 
 int tsl2583_set_pm_runtime_busy (struct tsl2583_chip*,int) ; 

__attribute__((used)) static int tsl2583_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct tsl2583_chip *chip = iio_priv(indio_dev);
	int ret;

	ret = tsl2583_set_pm_runtime_busy(chip, true);
	if (ret < 0)
		return ret;

	mutex_lock(&chip->als_mutex);

	ret = -EINVAL;
	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		if (chan->type == IIO_LIGHT) {
			chip->als_settings.als_gain_trim = val;
			ret = 0;
		}
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_LIGHT) {
			unsigned int i;

			for (i = 0; i < ARRAY_SIZE(gainadj); i++) {
				if (gainadj[i].mean == val) {
					chip->als_settings.als_gain = i;
					ret = tsl2583_set_als_gain(chip);
					break;
				}
			}
		}
		break;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_LIGHT && !val && val2 >= 50 &&
		    val2 <= 650 && !(val2 % 50)) {
			chip->als_settings.als_time = val2;
			ret = tsl2583_set_als_time(chip);
		}
		break;
	default:
		break;
	}

	mutex_unlock(&chip->als_mutex);

	if (ret < 0)
		return ret;

	ret = tsl2583_set_pm_runtime_busy(chip, false);
	if (ret < 0)
		return ret;

	return ret;
}