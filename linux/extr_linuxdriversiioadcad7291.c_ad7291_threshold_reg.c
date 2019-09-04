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
struct iio_chan_spec {int type; unsigned int channel; } ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 unsigned int AD7291_DATA_HIGH (unsigned int) ; 
 unsigned int AD7291_DATA_LOW (unsigned int) ; 
 unsigned int AD7291_HYST (unsigned int) ; 
 unsigned int AD7291_VOLTAGE_OFFSET ; 
 int IIO_EV_DIR_FALLING ; 
#define  IIO_EV_INFO_HYSTERESIS 131 
#define  IIO_EV_INFO_VALUE 130 
#define  IIO_TEMP 129 
#define  IIO_VOLTAGE 128 

__attribute__((used)) static unsigned int ad7291_threshold_reg(const struct iio_chan_spec *chan,
					 enum iio_event_direction dir,
					 enum iio_event_info info)
{
	unsigned int offset;

	switch (chan->type) {
	case IIO_VOLTAGE:
		offset = chan->channel;
		break;
	case IIO_TEMP:
		offset = AD7291_VOLTAGE_OFFSET;
		break;
	default:
	    return 0;
	}

	switch (info) {
	case IIO_EV_INFO_VALUE:
		if (dir == IIO_EV_DIR_FALLING)
			return AD7291_DATA_HIGH(offset);
		else
			return AD7291_DATA_LOW(offset);
	case IIO_EV_INFO_HYSTERESIS:
		return AD7291_HYST(offset);
	default:
		break;
	}
	return 0;
}