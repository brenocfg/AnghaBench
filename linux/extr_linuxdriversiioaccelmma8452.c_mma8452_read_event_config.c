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
struct mma8452_event_regs {scalar_t__ ev_cfg_chan_shift; int /*<<< orphan*/  ev_cfg; } ;
struct mma8452_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ scan_index; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int mma8452_freefall_mode_enabled (struct mma8452_data*) ; 
 int mma8452_get_event_regs (struct mma8452_data*,struct iio_chan_spec const*,int,struct mma8452_event_regs const**) ; 

__attribute__((used)) static int mma8452_read_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir)
{
	struct mma8452_data *data = iio_priv(indio_dev);
	int ret;
	const struct mma8452_event_regs *ev_regs;

	ret = mma8452_get_event_regs(data, chan, dir, &ev_regs);
	if (ret)
		return ret;

	switch (dir) {
	case IIO_EV_DIR_FALLING:
		return mma8452_freefall_mode_enabled(data);
	case IIO_EV_DIR_RISING:
		ret = i2c_smbus_read_byte_data(data->client,
				ev_regs->ev_cfg);
		if (ret < 0)
			return ret;

		return !!(ret & BIT(chan->scan_index +
				ev_regs->ev_cfg_chan_shift));
	default:
		return -EINVAL;
	}
}