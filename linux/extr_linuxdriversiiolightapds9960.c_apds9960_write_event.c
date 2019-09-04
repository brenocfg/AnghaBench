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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
struct apds9960_data {int /*<<< orphan*/  regmap; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int APDS9960_MAX_ALS_THRES_VAL ; 
 int APDS9960_MAX_PXS_THRES_VAL ; 
 int EINVAL ; 
 int IIO_EV_INFO_VALUE ; 
 scalar_t__ IIO_INTENSITY ; 
 scalar_t__ IIO_PROXIMITY ; 
 int apds9960_get_thres_reg (struct iio_chan_spec const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct apds9960_data* iio_priv (struct iio_dev*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds9960_write_event(struct iio_dev *indio_dev,
				const struct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_direction dir,
				enum iio_event_info info,
				int val, int val2)
{
	u8 reg;
	__le16 buf;
	int ret = 0;
	struct apds9960_data *data = iio_priv(indio_dev);

	if (info != IIO_EV_INFO_VALUE)
		return -EINVAL;

	ret = apds9960_get_thres_reg(chan, dir, &reg);
	if (ret < 0)
		return ret;

	if (chan->type == IIO_PROXIMITY) {
		if (val < 0 || val > APDS9960_MAX_PXS_THRES_VAL)
			return -EINVAL;
		ret = regmap_write(data->regmap, reg, val);
		if (ret < 0)
			return ret;
	} else if (chan->type == IIO_INTENSITY) {
		if (val < 0 || val > APDS9960_MAX_ALS_THRES_VAL)
			return -EINVAL;
		buf = cpu_to_le16(val);
		ret = regmap_bulk_write(data->regmap, reg, &buf, 2);
		if (ret < 0)
			return ret;
	} else
		return -EINVAL;

	return 0;
}