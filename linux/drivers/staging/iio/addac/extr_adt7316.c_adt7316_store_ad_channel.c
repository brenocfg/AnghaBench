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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int config2; int id; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ADT7316_AD_SINGLE_CH_MASK ; 
 int ADT7316_AD_SINGLE_CH_MODE ; 
 int /*<<< orphan*/  ADT7316_CONFIG2 ; 
 int ADT7516_AD_SINGLE_CH_MASK ; 
 size_t EINVAL ; 
 size_t EIO ; 
 size_t EPERM ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtou8 (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t adt7316_store_ad_channel(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config2;
	u8 data;
	int ret;

	if (!(chip->config2 & ADT7316_AD_SINGLE_CH_MODE))
		return -EPERM;

	ret = kstrtou8(buf, 10, &data);
	if (ret)
		return -EINVAL;

	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX) {
		if (data > 5)
			return -EINVAL;

		config2 = chip->config2 & (~ADT7516_AD_SINGLE_CH_MASK);
	} else {
		if (data > 2)
			return -EINVAL;

		config2 = chip->config2 & (~ADT7316_AD_SINGLE_CH_MASK);
	}

	config2 |= data;

	ret = chip->bus.write(chip->bus.client, ADT7316_CONFIG2, config2);
	if (ret)
		return -EIO;

	chip->config2 = config2;

	return len;
}