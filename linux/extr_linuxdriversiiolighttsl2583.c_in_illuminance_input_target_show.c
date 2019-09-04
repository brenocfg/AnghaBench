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
struct TYPE_2__ {int als_cal_target; } ;
struct tsl2583_chip {int /*<<< orphan*/  als_mutex; TYPE_1__ als_settings; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct tsl2583_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t in_illuminance_input_target_show(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct tsl2583_chip *chip = iio_priv(indio_dev);
	int ret;

	mutex_lock(&chip->als_mutex);
	ret = sprintf(buf, "%d\n", chip->als_settings.als_cal_target);
	mutex_unlock(&chip->als_mutex);

	return ret;
}