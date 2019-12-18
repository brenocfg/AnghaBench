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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7192_state {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  ad7192_get_available_filter_freq (struct ad7192_state*,unsigned int*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static ssize_t ad7192_show_filter_avail(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7192_state *st = iio_priv(indio_dev);
	unsigned int freq_avail[4], i;
	size_t len = 0;

	ad7192_get_available_filter_freq(st, freq_avail);

	for (i = 0; i < ARRAY_SIZE(freq_avail); i++)
		len += scnprintf(buf + len, PAGE_SIZE - len,
				 "%d.%d ", freq_avail[i] / 1000,
				 freq_avail[i] % 1000);

	buf[len - 1] = '\n';

	return len;
}