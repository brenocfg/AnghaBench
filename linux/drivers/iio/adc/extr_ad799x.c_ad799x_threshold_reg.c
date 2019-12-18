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
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 unsigned int AD7998_DATAHIGH_REG (int /*<<< orphan*/ ) ; 
 unsigned int AD7998_DATALOW_REG (int /*<<< orphan*/ ) ; 
 unsigned int AD7998_HYST_REG (int /*<<< orphan*/ ) ; 
 unsigned int EINVAL ; 
 int IIO_EV_DIR_FALLING ; 
#define  IIO_EV_INFO_HYSTERESIS 129 
#define  IIO_EV_INFO_VALUE 128 

__attribute__((used)) static unsigned int ad799x_threshold_reg(const struct iio_chan_spec *chan,
					 enum iio_event_direction dir,
					 enum iio_event_info info)
{
	switch (info) {
	case IIO_EV_INFO_VALUE:
		if (dir == IIO_EV_DIR_FALLING)
			return AD7998_DATALOW_REG(chan->channel);
		else
			return AD7998_DATAHIGH_REG(chan->channel);
	case IIO_EV_INFO_HYSTERESIS:
		return AD7998_HYST_REG(chan->channel);
	default:
		return -EINVAL;
	}

	return 0;
}