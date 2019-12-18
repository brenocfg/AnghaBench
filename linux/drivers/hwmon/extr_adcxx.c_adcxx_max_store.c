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
struct spi_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adcxx {unsigned long reference; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ERESTARTSYS ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct adcxx* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static ssize_t adcxx_max_store(struct device *dev,
			       struct device_attribute *devattr,
			       const char *buf, size_t count)
{
	struct spi_device *spi = to_spi_device(dev);
	struct adcxx *adc = spi_get_drvdata(spi);
	unsigned long value;

	if (kstrtoul(buf, 10, &value))
		return -EINVAL;

	if (mutex_lock_interruptible(&adc->lock))
		return -ERESTARTSYS;

	adc->reference = value;

	mutex_unlock(&adc->lock);

	return count;
}