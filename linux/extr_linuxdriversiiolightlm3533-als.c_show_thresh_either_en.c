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
struct lm3533_als {scalar_t__ irq; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int lm3533_als_get_int_mode (struct iio_dev*,int*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_thresh_either_en(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct lm3533_als *als = iio_priv(indio_dev);
	int enable;
	int ret;

	if (als->irq) {
		ret = lm3533_als_get_int_mode(indio_dev, &enable);
		if (ret)
			return ret;
	} else {
		enable = 0;
	}

	return scnprintf(buf, PAGE_SIZE, "%u\n", enable);
}