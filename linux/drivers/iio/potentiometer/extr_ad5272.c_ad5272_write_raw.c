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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct ad5272_data {TYPE_1__* cfg; } ;
struct TYPE_2__ {int max_pos; int shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5272_RDAC_WR ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 int ad5272_write (struct ad5272_data*,int /*<<< orphan*/ ,int) ; 
 struct ad5272_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5272_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct ad5272_data *data = iio_priv(indio_dev);

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	if (val >= data->cfg->max_pos || val < 0 || val2)
		return -EINVAL;

	return ad5272_write(data, AD5272_RDAC_WR, val << data->cfg->shift);
}