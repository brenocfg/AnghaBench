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
struct iio_chan_spec {int type; int /*<<< orphan*/  channel; } ;
struct ad7291_chip_info {int c_mask; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_TEMP 129 
#define  IIO_VOLTAGE 128 
 struct ad7291_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7291_read_event_config(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir)
{
	struct ad7291_chip_info *chip = iio_priv(indio_dev);
	/*
	 * To be enabled the channel must simply be on. If any are enabled
	 * we are in continuous sampling mode
	 */

	switch (chan->type) {
	case IIO_VOLTAGE:
		return !!(chip->c_mask & BIT(15 - chan->channel));
	case IIO_TEMP:
		/* always on */
		return 1;
	default:
		return -EINVAL;
	}

}