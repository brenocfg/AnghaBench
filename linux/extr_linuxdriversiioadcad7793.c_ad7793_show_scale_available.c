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
struct ad7793_state {int** scale_avail; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7793_state* iio_priv (struct iio_dev*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t ad7793_show_scale_available(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7793_state *st = iio_priv(indio_dev);
	int i, len = 0;

	for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
		len += sprintf(buf + len, "%d.%09u ", st->scale_avail[i][0],
			       st->scale_avail[i][1]);

	len += sprintf(buf + len, "\n");

	return len;
}