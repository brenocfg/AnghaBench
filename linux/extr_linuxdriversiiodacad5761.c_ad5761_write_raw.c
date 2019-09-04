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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int shift; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5761_ADDR_DAC_WRITE ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 int ad5761_spi_write (struct iio_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad5761_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	u16 aux;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	if (val2 || (val << chan->scan_type.shift) > 0xffff || val < 0)
		return -EINVAL;

	aux = val << chan->scan_type.shift;

	return ad5761_spi_write(indio_dev, AD5761_ADDR_DAC_WRITE, aux);
}