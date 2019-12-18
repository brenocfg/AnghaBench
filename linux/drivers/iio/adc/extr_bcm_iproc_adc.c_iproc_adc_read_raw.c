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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 128 
 int iproc_adc_do_read (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int iproc_adc_read_raw(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan,
			  int *val,
			  int *val2,
			  long mask)
{
	u16 adc_data;
	int err;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		err =  iproc_adc_do_read(indio_dev, chan->channel, &adc_data);
		if (err < 0)
			return err;
		*val = adc_data;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			*val = 1800;
			*val2 = 10;
			return IIO_VAL_FRACTIONAL_LOG2;
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}