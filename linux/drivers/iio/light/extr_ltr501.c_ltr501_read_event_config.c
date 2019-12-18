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
struct ltr501_data {int /*<<< orphan*/  reg_ps_intr; int /*<<< orphan*/  reg_als_intr; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 struct ltr501_data* iio_priv (struct iio_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ltr501_read_event_config(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int ret, status;

	switch (chan->type) {
	case IIO_INTENSITY:
		ret = regmap_field_read(data->reg_als_intr, &status);
		if (ret < 0)
			return ret;
		return status;
	case IIO_PROXIMITY:
		ret = regmap_field_read(data->reg_ps_intr, &status);
		if (ret < 0)
			return ret;
		return status;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}