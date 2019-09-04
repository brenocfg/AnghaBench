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
struct tsl2563_chip {int data0; int cover_comp_gain; int data1; int /*<<< orphan*/  lock; int /*<<< orphan*/  calib1; int /*<<< orphan*/  calib0; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 132 
#define  IIO_CHAN_INFO_PROCESSED 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_INTENSITY 129 
#define  IIO_LIGHT 128 
 int /*<<< orphan*/  IIO_MOD_LIGHT_BOTH ; 
 int IIO_VAL_INT ; 
 struct tsl2563_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsl2563_adc_to_lux (int,int) ; 
 int tsl2563_calib_adc (int,int /*<<< orphan*/ ) ; 
 int tsl2563_calib_to_sysfs (int /*<<< orphan*/ ) ; 
 int tsl2563_get_adc (struct tsl2563_chip*) ; 

__attribute__((used)) static int tsl2563_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val,
			    int *val2,
			    long mask)
{
	int ret = -EINVAL;
	u32 calib0, calib1;
	struct tsl2563_chip *chip = iio_priv(indio_dev);

	mutex_lock(&chip->lock);
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_LIGHT:
			ret = tsl2563_get_adc(chip);
			if (ret)
				goto error_ret;
			calib0 = tsl2563_calib_adc(chip->data0, chip->calib0) *
				chip->cover_comp_gain;
			calib1 = tsl2563_calib_adc(chip->data1, chip->calib1) *
				chip->cover_comp_gain;
			*val = tsl2563_adc_to_lux(calib0, calib1);
			ret = IIO_VAL_INT;
			break;
		case IIO_INTENSITY:
			ret = tsl2563_get_adc(chip);
			if (ret)
				goto error_ret;
			if (chan->channel2 == IIO_MOD_LIGHT_BOTH)
				*val = chip->data0;
			else
				*val = chip->data1;
			ret = IIO_VAL_INT;
			break;
		default:
			break;
		}
		break;

	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->channel2 == IIO_MOD_LIGHT_BOTH)
			*val = tsl2563_calib_to_sysfs(chip->calib0);
		else
			*val = tsl2563_calib_to_sysfs(chip->calib1);
		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		goto error_ret;
	}

error_ret:
	mutex_unlock(&chip->lock);
	return ret;
}