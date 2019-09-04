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
struct iio_chan_spec {scalar_t__ channel; int /*<<< orphan*/  address; } ;
struct da9150_gpadc {int dummy; } ;

/* Variables and functions */
 scalar_t__ DA9150_GPADC_CHAN_GPIOA ; 
 scalar_t__ DA9150_GPADC_CHAN_TJUNC_OVP ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int da9150_gpadc_read_offset (scalar_t__,int*) ; 
 int da9150_gpadc_read_processed (struct da9150_gpadc*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int da9150_gpadc_read_scale (scalar_t__,int*,int*) ; 
 struct da9150_gpadc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int da9150_gpadc_read_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int *val, int *val2, long mask)
{
	struct da9150_gpadc *gpadc = iio_priv(indio_dev);

	if ((chan->channel < DA9150_GPADC_CHAN_GPIOA) ||
	    (chan->channel > DA9150_GPADC_CHAN_TJUNC_OVP))
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		return da9150_gpadc_read_processed(gpadc, chan->channel,
						   chan->address, val);
	case IIO_CHAN_INFO_SCALE:
		return da9150_gpadc_read_scale(chan->channel, val, val2);
	case IIO_CHAN_INFO_OFFSET:
		return da9150_gpadc_read_offset(chan->channel, val);
	default:
		return -EINVAL;
	}
}