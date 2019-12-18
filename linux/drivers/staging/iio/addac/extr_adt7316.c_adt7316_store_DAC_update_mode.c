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
struct adt7316_chip_info {int config3; int dac_config; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_DAC_CONFIG ; 
 int ADT7316_DA_EN_MODE_MASK ; 
 int ADT7316_DA_EN_MODE_SHIFT ; 
 int ADT7316_DA_EN_VIA_DAC_LDAC ; 
 size_t EINVAL ; 
 size_t EIO ; 
 size_t EPERM ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtou8 (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t adt7316_store_DAC_update_mode(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf,
					     size_t len)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u8 dac_config;
	u8 data;
	int ret;

	if (!(chip->config3 & ADT7316_DA_EN_VIA_DAC_LDAC))
		return -EPERM;

	ret = kstrtou8(buf, 10, &data);
	if (ret || data > (ADT7316_DA_EN_MODE_MASK >> ADT7316_DA_EN_MODE_SHIFT))
		return -EINVAL;

	dac_config = chip->dac_config & (~ADT7316_DA_EN_MODE_MASK);
	dac_config |= data << ADT7316_DA_EN_MODE_SHIFT;

	ret = chip->bus.write(chip->bus.client, ADT7316_DAC_CONFIG, dac_config);
	if (ret)
		return -EIO;

	chip->dac_config = dac_config;

	return len;
}