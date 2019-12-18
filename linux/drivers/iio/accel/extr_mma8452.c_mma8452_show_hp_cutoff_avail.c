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
struct mma8452_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 int mma8452_get_power_mode (struct mma8452_data*) ; 
 int /*<<< orphan*/ ** mma8452_hp_filter_cutoff ; 
 int mma8452_show_int_plus_micros (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t mma8452_show_hp_cutoff_avail(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct mma8452_data *data = iio_priv(indio_dev);
	int i, j;

	i = mma8452_get_odr_index(data);
	j = mma8452_get_power_mode(data);
	if (j < 0)
		return j;

	return mma8452_show_int_plus_micros(buf, mma8452_hp_filter_cutoff[j][i],
		ARRAY_SIZE(mma8452_hp_filter_cutoff[0][0]));
}