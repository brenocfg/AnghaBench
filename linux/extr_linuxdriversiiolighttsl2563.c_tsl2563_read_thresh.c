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
struct tsl2563_chip {int high_thres; int low_thres; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 int IIO_VAL_INT ; 
 struct tsl2563_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int tsl2563_read_thresh(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info, int *val,
	int *val2)
{
	struct tsl2563_chip *chip = iio_priv(indio_dev);

	switch (dir) {
	case IIO_EV_DIR_RISING:
		*val = chip->high_thres;
		break;
	case IIO_EV_DIR_FALLING:
		*val = chip->low_thres;
		break;
	default:
		return -EINVAL;
	}

	return IIO_VAL_INT;
}