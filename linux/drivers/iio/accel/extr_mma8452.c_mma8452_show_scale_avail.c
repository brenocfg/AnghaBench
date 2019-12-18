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
struct mma8452_data {TYPE_1__* chip_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mma_scales; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 struct mma8452_data* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mma8452_show_int_plus_micros (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t mma8452_show_scale_avail(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct mma8452_data *data = iio_priv(i2c_get_clientdata(
					     to_i2c_client(dev)));

	return mma8452_show_int_plus_micros(buf, data->chip_info->mma_scales,
		ARRAY_SIZE(data->chip_info->mma_scales));
}