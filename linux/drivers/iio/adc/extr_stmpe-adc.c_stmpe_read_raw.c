#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stmpe_adc {TYPE_1__* stmpe; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  mod_12b; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 struct stmpe_adc* iio_priv (struct iio_dev*) ; 
 long stmpe_read_temp (struct stmpe_adc*,struct iio_chan_spec const*,int*) ; 
 long stmpe_read_voltage (struct stmpe_adc*,struct iio_chan_spec const*,int*) ; 

__attribute__((used)) static int stmpe_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val,
			  int *val2,
			  long mask)
{
	struct stmpe_adc *info = iio_priv(indio_dev);
	long ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:

		switch (chan->type) {
		case IIO_VOLTAGE:
			ret = stmpe_read_voltage(info, chan, val);
			break;

		case IIO_TEMP:
			ret = stmpe_read_temp(info, chan, val);
			break;
		default:
			return -EINVAL;
		}

		if (ret < 0)
			return ret;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = 3300;
		*val2 = info->stmpe->mod_12b ? 12 : 10;
		return IIO_VAL_FRACTIONAL_LOG2;

	default:
		break;
	}

	return -EINVAL;
}