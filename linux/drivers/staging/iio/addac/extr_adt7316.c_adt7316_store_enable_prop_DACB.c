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
struct adt7316_chip_info {int config3; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_CONFIG3 ; 
 int ADT7316_EN_EX_TEMP_PROP_DACB ; 
 size_t EIO ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t adt7316_store_enable_prop_DACB(struct device *dev,
					      struct device_attribute *attr,
					      const char *buf,
					      size_t len)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u8 config3;
	int ret;

	config3 = chip->config3 & (~ADT7316_EN_EX_TEMP_PROP_DACB);
	if (buf[0] == '1')
		config3 |= ADT7316_EN_EX_TEMP_PROP_DACB;

	ret = chip->bus.write(chip->bus.client, ADT7316_CONFIG3, config3);
	if (ret)
		return -EIO;

	chip->config3 = config3;

	return len;
}