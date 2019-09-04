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
struct isl29018_chip {size_t int_time; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int scale; int uscale; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct isl29018_chip* iio_priv (struct iio_dev*) ; 
 TYPE_1__** isl29018_scales ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t in_illuminance_scale_available_show
			(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct isl29018_chip *chip = iio_priv(indio_dev);
	unsigned int i;
	int len = 0;

	mutex_lock(&chip->lock);
	for (i = 0; i < ARRAY_SIZE(isl29018_scales[chip->int_time]); ++i)
		len += sprintf(buf + len, "%d.%06d ",
			       isl29018_scales[chip->int_time][i].scale,
			       isl29018_scales[chip->int_time][i].uscale);
	mutex_unlock(&chip->lock);

	buf[len - 1] = '\n';

	return len;
}