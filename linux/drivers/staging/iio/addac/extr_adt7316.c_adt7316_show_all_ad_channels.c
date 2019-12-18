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
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7316_chip_info {int config2; int id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ADT7316_AD_SINGLE_CH_MODE ; 
 int /*<<< orphan*/  EPERM ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t adt7316_show_all_ad_channels(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);

	if (!(chip->config2 & ADT7316_AD_SINGLE_CH_MODE))
		return -EPERM;

	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		return sprintf(buf, "0 - VDD\n1 - Internal Temperature\n"
				"2 - External Temperature or AIN1\n"
				"3 - AIN2\n4 - AIN3\n5 - AIN4\n");
	return sprintf(buf, "0 - VDD\n1 - Internal Temperature\n"
			"2 - External Temperature\n");
}