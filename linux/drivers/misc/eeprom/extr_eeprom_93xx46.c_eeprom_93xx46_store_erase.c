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
struct eeprom_93xx46_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct eeprom_93xx46_dev* dev_get_drvdata (struct device*) ; 
 int eeprom_93xx46_eral (struct eeprom_93xx46_dev*) ; 
 int eeprom_93xx46_ew (struct eeprom_93xx46_dev*,int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t eeprom_93xx46_store_erase(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct eeprom_93xx46_dev *edev = dev_get_drvdata(dev);
	int erase = 0, ret;

	sscanf(buf, "%d", &erase);
	if (erase) {
		ret = eeprom_93xx46_ew(edev, 1);
		if (ret)
			return ret;
		ret = eeprom_93xx46_eral(edev);
		if (ret)
			return ret;
		ret = eeprom_93xx46_ew(edev, 0);
		if (ret)
			return ret;
	}
	return count;
}