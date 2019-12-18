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
struct adxl372_state {int odr; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * adxl372_bw_freq_tbl ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t adxl372_show_filter_freq_avail(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct adxl372_state *st = iio_priv(indio_dev);
	int i;
	size_t len = 0;

	for (i = 0; i <= st->odr; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len,
				 "%d ", adxl372_bw_freq_tbl[i]);

	buf[len - 1] = '\n';

	return len;
}