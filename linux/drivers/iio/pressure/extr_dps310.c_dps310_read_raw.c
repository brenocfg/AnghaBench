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
struct iio_chan_spec {int type; } ;
struct dps310_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int dps310_read_pressure (struct dps310_data*,int*,int*,long) ; 
 int dps310_read_temp (struct dps310_data*,int*,int*,long) ; 
 struct dps310_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int dps310_read_raw(struct iio_dev *iio,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct dps310_data *data = iio_priv(iio);

	switch (chan->type) {
	case IIO_PRESSURE:
		return dps310_read_pressure(data, val, val2, mask);

	case IIO_TEMP:
		return dps310_read_temp(data, val, val2, mask);

	default:
		return -EINVAL;
	}
}