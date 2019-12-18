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
typedef  int /*<<< orphan*/  u32 ;
struct isl29501_private {int dummy; } ;
struct iio_chan_spec {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int**) ; 
 int EINVAL ; 
#define  IIO_CURRENT 132 
#define  IIO_INTENSITY 131 
#define  IIO_PHASE 130 
#define  IIO_PROXIMITY 129 
#define  IIO_TEMP 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  REG_DRIVER_RANGE ; 
 int** isl29501_current_scale_table ; 
 int isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isl29501_get_scale(struct isl29501_private *isl29501,
			      const struct iio_chan_spec *chan,
			      int *val, int *val2)
{
	int ret;
	u32 current_scale;

	switch (chan->type) {
	case IIO_PROXIMITY:
		/* distance = raw_distance * 33.31 / 65536 (m) */
		*val = 3331;
		*val2 = 6553600;

		return IIO_VAL_FRACTIONAL;
	case IIO_PHASE:
		/* phase = raw_phase * 2pi / 65536 (rad) */
		*val = 0;
		*val2 = 95874;

		return IIO_VAL_INT_PLUS_NANO;
	case IIO_INTENSITY:
		/* light = raw_light * 35 / 10000 (mA) */
		*val = 35;
		*val2 = 10000;

		return IIO_VAL_FRACTIONAL;
	case IIO_CURRENT:
		ret = isl29501_register_read(isl29501,
					     REG_DRIVER_RANGE,
					     &current_scale);
		if (ret < 0)
			return ret;

		if (current_scale > ARRAY_SIZE(isl29501_current_scale_table))
			return -EINVAL;

		if (!current_scale) {
			*val = 0;
			*val2 = 0;
			return IIO_VAL_INT;
		}

		*val = isl29501_current_scale_table[current_scale - 1][0];
		*val2 = isl29501_current_scale_table[current_scale - 1][1];

		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_TEMP:
		/* temperature = raw_temperature * 125 / 100000 (milli °C) */
		*val = 125;
		*val2 = 100000;

		return IIO_VAL_FRACTIONAL;
	default:
		return -EINVAL;
	}
}