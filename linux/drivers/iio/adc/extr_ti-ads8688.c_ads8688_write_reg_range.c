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
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
typedef  enum ads8688_range { ____Placeholder_ads8688_range } ads8688_range ;

/* Variables and functions */
 unsigned int ADS8688_PROG_REG_RANGE_CH (int /*<<< orphan*/ ) ; 
 int ads8688_prog_write (struct iio_dev*,unsigned int,int) ; 

__attribute__((used)) static int ads8688_write_reg_range(struct iio_dev *indio_dev,
				   struct iio_chan_spec const *chan,
				   enum ads8688_range range)
{
	unsigned int tmp;
	int ret;

	tmp = ADS8688_PROG_REG_RANGE_CH(chan->channel);
	ret = ads8688_prog_write(indio_dev, tmp, range);

	return ret;
}