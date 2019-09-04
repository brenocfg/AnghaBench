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
struct ina2xx_chip_info {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ina2xx_chip_info* iio_priv (int /*<<< orphan*/ ) ; 
 int iio_str_to_fixpoint (char const*,int,int*,int*) ; 
 int set_shunt_resistor (struct ina2xx_chip_info*,int) ; 

__attribute__((used)) static ssize_t ina2xx_shunt_resistor_store(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t len)
{
	struct ina2xx_chip_info *chip = iio_priv(dev_to_iio_dev(dev));
	int val, val_fract, ret;

	ret = iio_str_to_fixpoint(buf, 100000, &val, &val_fract);
	if (ret)
		return ret;

	ret = set_shunt_resistor(chip, val * 1000000 + val_fract);
	if (ret)
		return ret;

	return len;
}