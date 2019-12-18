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
struct ltr501_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 131 
#define  IIO_EV_DIR_RISING 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  LTR501_ALS_THRESH_LOW ; 
 int LTR501_ALS_THRESH_MASK ; 
 int /*<<< orphan*/  LTR501_ALS_THRESH_UP ; 
 int /*<<< orphan*/  LTR501_PS_THRESH_LOW ; 
 int LTR501_PS_THRESH_MASK ; 
 int /*<<< orphan*/  LTR501_PS_THRESH_UP ; 
 struct ltr501_data* iio_priv (struct iio_dev*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltr501_read_thresh(struct iio_dev *indio_dev,
			      const struct iio_chan_spec *chan,
			      enum iio_event_type type,
			      enum iio_event_direction dir,
			      enum iio_event_info info,
			      int *val, int *val2)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int ret, thresh_data;

	switch (chan->type) {
	case IIO_INTENSITY:
		switch (dir) {
		case IIO_EV_DIR_RISING:
			ret = regmap_bulk_read(data->regmap,
					       LTR501_ALS_THRESH_UP,
					       &thresh_data, 2);
			if (ret < 0)
				return ret;
			*val = thresh_data & LTR501_ALS_THRESH_MASK;
			return IIO_VAL_INT;
		case IIO_EV_DIR_FALLING:
			ret = regmap_bulk_read(data->regmap,
					       LTR501_ALS_THRESH_LOW,
					       &thresh_data, 2);
			if (ret < 0)
				return ret;
			*val = thresh_data & LTR501_ALS_THRESH_MASK;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_PROXIMITY:
		switch (dir) {
		case IIO_EV_DIR_RISING:
			ret = regmap_bulk_read(data->regmap,
					       LTR501_PS_THRESH_UP,
					       &thresh_data, 2);
			if (ret < 0)
				return ret;
			*val = thresh_data & LTR501_PS_THRESH_MASK;
			return IIO_VAL_INT;
		case IIO_EV_DIR_FALLING:
			ret = regmap_bulk_read(data->regmap,
					       LTR501_PS_THRESH_LOW,
					       &thresh_data, 2);
			if (ret < 0)
				return ret;
			*val = thresh_data & LTR501_PS_THRESH_MASK;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}

	return -EINVAL;
}