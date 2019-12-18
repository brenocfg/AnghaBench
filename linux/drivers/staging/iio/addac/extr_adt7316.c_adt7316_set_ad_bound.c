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
typedef  scalar_t__ u8 ;
struct iio_dev_attr {scalar_t__ address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int id; int config1; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ ADT7316_EX_TEMP_LOW ; 
 int ADT7516_SEL_AIN1_2_EX_TEMP_MASK ; 
 size_t EINVAL ; 
 size_t EIO ; 
 size_t EPERM ; 
 int ID_ADT73XX ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtoint (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static inline ssize_t adt7316_set_ad_bound(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf,
					   size_t len)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	int data;
	u8 val;
	int ret;

	if ((chip->id & ID_FAMILY_MASK) == ID_ADT73XX &&
	    this_attr->address > ADT7316_EX_TEMP_LOW)
		return -EPERM;

	ret = kstrtoint(buf, 10, &data);
	if (ret)
		return -EINVAL;

	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX &&
	    (chip->config1 & ADT7516_SEL_AIN1_2_EX_TEMP_MASK) == 0) {
		if (data > 255 || data < 0)
			return -EINVAL;
	} else {
		if (data > 127 || data < -128)
			return -EINVAL;

		if (data < 0)
			data += 256;
	}

	val = (u8)data;

	ret = chip->bus.write(chip->bus.client, this_attr->address, val);
	if (ret)
		return -EIO;

	return len;
}