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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bmp280_data {TYPE_1__* chip_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  num_oversampling_temp_avail; int /*<<< orphan*/  oversampling_temp_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmp280_show_avail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct bmp280_data* iio_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bmp280_show_temp_oversampling_avail(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct bmp280_data *data = iio_priv(dev_to_iio_dev(dev));

	return bmp280_show_avail(buf, data->chip_info->oversampling_temp_avail,
				 data->chip_info->num_oversampling_temp_avail);
}