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
struct bma180_data {TYPE_1__* part_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  num_bw; int /*<<< orphan*/  bw_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  bma180_show_avail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct bma180_data* iio_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t bma180_show_filter_freq_avail(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct bma180_data *data = iio_priv(dev_to_iio_dev(dev));

	return bma180_show_avail(buf, data->part_info->bw_table,
		data->part_info->num_bw, false);
}