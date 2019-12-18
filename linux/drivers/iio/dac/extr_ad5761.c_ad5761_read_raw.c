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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {int shift; int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct ad5761_state {int vref; size_t range; } ;
struct TYPE_4__ {int m; int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5761_ADDR_DAC_READ ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 TYPE_2__* ad5761_range_params ; 
 int ad5761_spi_read (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 struct ad5761_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5761_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long mask)
{
	struct ad5761_state *st;
	int ret;
	u16 aux;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = ad5761_spi_read(indio_dev, AD5761_ADDR_DAC_READ, &aux);
		if (ret)
			return ret;
		*val = aux >> chan->scan_type.shift;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		st = iio_priv(indio_dev);
		*val = st->vref * ad5761_range_params[st->range].m;
		*val /= 10;
		*val2 = chan->scan_type.realbits;
		return IIO_VAL_FRACTIONAL_LOG2;
	case IIO_CHAN_INFO_OFFSET:
		st = iio_priv(indio_dev);
		*val = -(1 << chan->scan_type.realbits);
		*val *=	ad5761_range_params[st->range].c;
		*val /=	ad5761_range_params[st->range].m;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}