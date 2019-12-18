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
struct adt7316_chip_info {int id; int ldac_config; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ADT7316_DAC_IN_VREF ; 
 int /*<<< orphan*/  ADT7316_LDAC_CONFIG ; 
 int ADT7516_DAC_AB_IN_VREF ; 
 int ADT7516_DAC_CD_IN_VREF ; 
 int ADT7516_DAC_IN_VREF_MASK ; 
 size_t EINVAL ; 
 size_t EIO ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtou8 (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t adt7316_store_DAC_internal_Vref(struct device *dev,
					       struct device_attribute *attr,
					       const char *buf,
					       size_t len)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u8 ldac_config;
	u8 data;
	int ret;

	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX) {
		ret = kstrtou8(buf, 16, &data);
		if (ret || data > 3)
			return -EINVAL;

		ldac_config = chip->ldac_config & (~ADT7516_DAC_IN_VREF_MASK);
		if (data & 0x1)
			ldac_config |= ADT7516_DAC_AB_IN_VREF;
		if (data & 0x2)
			ldac_config |= ADT7516_DAC_CD_IN_VREF;
	} else {
		ret = kstrtou8(buf, 16, &data);
		if (ret)
			return -EINVAL;

		ldac_config = chip->ldac_config & (~ADT7316_DAC_IN_VREF);
		if (data)
			ldac_config = chip->ldac_config | ADT7316_DAC_IN_VREF;
	}

	ret = chip->bus.write(chip->bus.client, ADT7316_LDAC_CONFIG,
			ldac_config);
	if (ret)
		return -EIO;

	chip->ldac_config = ldac_config;

	return len;
}