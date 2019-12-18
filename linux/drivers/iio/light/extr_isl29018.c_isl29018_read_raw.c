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
struct TYPE_2__ {int scale; int uscale; } ;
struct isl29018_chip {size_t type; size_t int_time; int calibscale; int ucalibscale; int /*<<< orphan*/  lock; TYPE_1__ scale; int /*<<< orphan*/  prox_scheme; scalar_t__ suspended; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int const type; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 135 
#define  IIO_CHAN_INFO_INT_TIME 134 
#define  IIO_CHAN_INFO_PROCESSED 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_INTENSITY 130 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct isl29018_chip* iio_priv (struct iio_dev*) ; 
 int** isl29018_int_utimes ; 
 int isl29018_read_ir (struct isl29018_chip*,int*) ; 
 int isl29018_read_lux (struct isl29018_chip*,int*) ; 
 int isl29018_read_proximity_ir (struct isl29018_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isl29018_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long mask)
{
	int ret = -EINVAL;
	struct isl29018_chip *chip = iio_priv(indio_dev);

	mutex_lock(&chip->lock);
	if (chip->suspended) {
		ret = -EBUSY;
		goto read_done;
	}
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		switch (chan->type) {
		case IIO_LIGHT:
			ret = isl29018_read_lux(chip, val);
			break;
		case IIO_INTENSITY:
			ret = isl29018_read_ir(chip, val);
			break;
		case IIO_PROXIMITY:
			ret = isl29018_read_proximity_ir(chip,
							 chip->prox_scheme,
							 val);
			break;
		default:
			break;
		}
		if (!ret)
			ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_INT_TIME:
		if (chan->type == IIO_LIGHT) {
			*val = 0;
			*val2 = isl29018_int_utimes[chip->type][chip->int_time];
			ret = IIO_VAL_INT_PLUS_MICRO;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_LIGHT) {
			*val = chip->scale.scale;
			*val2 = chip->scale.uscale;
			ret = IIO_VAL_INT_PLUS_MICRO;
		}
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (chan->type == IIO_LIGHT) {
			*val = chip->calibscale;
			*val2 = chip->ucalibscale;
			ret = IIO_VAL_INT_PLUS_MICRO;
		}
		break;
	default:
		break;
	}

read_done:
	mutex_unlock(&chip->lock);

	return ret;
}