#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bmc150_magn_data {scalar_t__ max_odr; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ freq; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_1__* bmc150_magn_samp_freq_table ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static ssize_t bmc150_magn_show_samp_freq_avail(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	size_t len = 0;
	u8 i;

	for (i = 0; i < ARRAY_SIZE(bmc150_magn_samp_freq_table); i++) {
		if (bmc150_magn_samp_freq_table[i].freq > data->max_odr)
			break;
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
				 bmc150_magn_samp_freq_table[i].freq);
	}
	/* replace last space with a newline */
	buf[len - 1] = '\n';

	return len;
}