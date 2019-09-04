#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int shift; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; TYPE_1__ scan_type; } ;
struct ad5755_state {TYPE_2__* chip_info; } ;
struct TYPE_4__ {unsigned int calib_shift; } ;

/* Variables and functions */
 unsigned int AD5755_READ_REG_DATA (int /*<<< orphan*/ ) ; 
 unsigned int AD5755_READ_REG_GAIN (int /*<<< orphan*/ ) ; 
 unsigned int AD5755_READ_REG_OFFSET (int /*<<< orphan*/ ) ; 
 unsigned int AD5755_WRITE_REG_DATA (int /*<<< orphan*/ ) ; 
 unsigned int AD5755_WRITE_REG_GAIN (int /*<<< orphan*/ ) ; 
 unsigned int AD5755_WRITE_REG_OFFSET (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_RAW 128 

__attribute__((used)) static int ad5755_chan_reg_info(struct ad5755_state *st,
	struct iio_chan_spec const *chan, long info, bool write,
	unsigned int *reg, unsigned int *shift, unsigned int *offset)
{
	switch (info) {
	case IIO_CHAN_INFO_RAW:
		if (write)
			*reg = AD5755_WRITE_REG_DATA(chan->address);
		else
			*reg = AD5755_READ_REG_DATA(chan->address);
		*shift = chan->scan_type.shift;
		*offset = 0;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		if (write)
			*reg = AD5755_WRITE_REG_OFFSET(chan->address);
		else
			*reg = AD5755_READ_REG_OFFSET(chan->address);
		*shift = st->chip_info->calib_shift;
		*offset = 32768;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		if (write)
			*reg =  AD5755_WRITE_REG_GAIN(chan->address);
		else
			*reg =  AD5755_READ_REG_GAIN(chan->address);
		*shift = st->chip_info->calib_shift;
		*offset = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}