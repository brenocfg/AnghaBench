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
struct isl29018_chip {int prox_scheme; int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct isl29018_chip* iio_priv (struct iio_dev*) ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t proximity_on_chip_ambient_infrared_suppression_store
			(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct isl29018_chip *chip = iio_priv(indio_dev);
	int val;

	if (kstrtoint(buf, 10, &val))
		return -EINVAL;
	if (!(val == 0 || val == 1))
		return -EINVAL;

	/*
	 * Get the "proximity scheme" i.e. if the chip does on chip
	 * infrared suppression (1 means perform on chip suppression)
	 */
	mutex_lock(&chip->lock);
	chip->prox_scheme = val;
	mutex_unlock(&chip->lock);

	return count;
}