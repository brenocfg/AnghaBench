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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int lm3533_als_get_zone (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_zone(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	u8 zone;
	int ret;

	ret = lm3533_als_get_zone(indio_dev, &zone);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "%u\n", zone);
}