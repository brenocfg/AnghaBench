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
struct iio_chan_spec {int dummy; } ;
struct ad5755_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ad5755_chan_reg_info (struct ad5755_state*,struct iio_chan_spec const*,long,int,unsigned int*,unsigned int*,unsigned int*) ; 
 int ad5755_write (struct iio_dev*,unsigned int,int) ; 
 struct ad5755_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5755_write_raw(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int val, int val2, long info)
{
	struct ad5755_state *st = iio_priv(indio_dev);
	unsigned int shift, reg, offset;
	int ret;

	ret = ad5755_chan_reg_info(st, chan, info, true,
					&reg, &shift, &offset);
	if (ret)
		return ret;

	val <<= shift;
	val += offset;

	if (val < 0 || val > 0xffff)
		return -EINVAL;

	return ad5755_write(indio_dev, reg, val);
}