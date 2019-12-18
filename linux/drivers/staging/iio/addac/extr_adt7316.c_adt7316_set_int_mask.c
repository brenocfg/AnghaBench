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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int int_mask; int id; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_INT_MASK1 ; 
 int /*<<< orphan*/  ADT7316_INT_MASK2 ; 
 int ADT7316_INT_MASK2_VDD ; 
 int ADT7316_TEMP_AIN_INT_MASK ; 
 int ADT7316_TEMP_INT_MASK ; 
 int ADT7316_VDD_INT_MASK ; 
 size_t EINVAL ; 
 int ID_ADT73XX ; 
 int ID_FAMILY_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtou16 (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t adt7316_set_int_mask(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);
	u16 data;
	int ret;
	u8 mask;

	ret = kstrtou16(buf, 16, &data);
	if (ret || data >= ADT7316_VDD_INT_MASK + 1)
		return -EINVAL;

	if (data & ADT7316_VDD_INT_MASK)
		mask = 0;			/* enable vdd int */
	else
		mask = ADT7316_INT_MASK2_VDD;	/* disable vdd int */

	ret = chip->bus.write(chip->bus.client, ADT7316_INT_MASK2, mask);
	if (!ret) {
		chip->int_mask &= ~ADT7316_VDD_INT_MASK;
		chip->int_mask |= data & ADT7316_VDD_INT_MASK;
	}

	if (data & ADT7316_TEMP_AIN_INT_MASK) {
		if ((chip->id & ID_FAMILY_MASK) == ID_ADT73XX)
			/* mask in reg is opposite, set 1 to disable */
			mask = (~data) & ADT7316_TEMP_INT_MASK;
		else
			/* mask in reg is opposite, set 1 to disable */
			mask = (~data) & ADT7316_TEMP_AIN_INT_MASK;
	}
	ret = chip->bus.write(chip->bus.client, ADT7316_INT_MASK1, mask);

	chip->int_mask = mask;

	return len;
}