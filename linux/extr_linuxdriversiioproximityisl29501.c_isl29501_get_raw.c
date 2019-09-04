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
struct isl29501_private {int dummy; } ;
struct iio_chan_spec {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CURRENT 132 
#define  IIO_INTENSITY 131 
#define  IIO_PHASE 130 
#define  IIO_PROXIMITY 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  REG_AMBIENT_LIGHT ; 
 int /*<<< orphan*/  REG_DISTANCE ; 
 int /*<<< orphan*/  REG_EMITTER_DAC ; 
 int /*<<< orphan*/  REG_PHASE ; 
 int /*<<< orphan*/  REG_TEMPERATURE ; 
 int isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int isl29501_get_raw(struct isl29501_private *isl29501,
			    const struct iio_chan_spec *chan,
			    int *raw)
{
	int ret;

	switch (chan->type) {
	case IIO_PROXIMITY:
		ret = isl29501_register_read(isl29501, REG_DISTANCE, raw);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	case IIO_INTENSITY:
		ret = isl29501_register_read(isl29501,
					     REG_AMBIENT_LIGHT,
					     raw);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	case IIO_PHASE:
		ret = isl29501_register_read(isl29501, REG_PHASE, raw);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	case IIO_CURRENT:
		ret = isl29501_register_read(isl29501, REG_EMITTER_DAC, raw);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	case IIO_TEMP:
		ret = isl29501_register_read(isl29501, REG_TEMPERATURE, raw);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}